#!/usr/bin/env python3
import json
import os
import time
import socket
import logging
from datetime import datetime, timezone

import serial
import serial.tools.list_ports
import paho.mqtt.client as mqtt

MQTT_BROKER = os.getenv('MQTT_BROKER', 'localhost')
MQTT_PORT = int(os.getenv('MQTT_PORT', '1883'))
MQTT_BASE_TOPIC = os.getenv('MQTT_BASE_TOPIC', 'minismartbus/rc_car')
MQTT_JSON_TOPIC = os.getenv('MQTT_JSON_TOPIC', f'{MQTT_BASE_TOPIC}/state')
SERIAL_PORT = os.getenv('SERIAL_PORT', '/dev/ttyACM0')
SERIAL_BAUD = int(os.getenv('SERIAL_BAUD', '115200'))
SERIAL_TIMEOUT = float(os.getenv('SERIAL_TIMEOUT', '1.0'))
PUBLISH_INTERVAL = float(os.getenv('PUBLISH_INTERVAL', '0.2'))
DISCOVERY_ENABLED = os.getenv('SERIAL_AUTO_DISCOVER', '1') == '1'

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s %(levelname)s %(message)s'
)
logger = logging.getLogger('rc-car-serial-mqtt')

state = {
    'timestamp': None,
    'host': socket.gethostname(),
    'source': 'arduino_rc_car',
    'rc': {
        'signal': None,
        'status': None,
        'ch1_us': None,
        'ch2_us': None,
    },
    'steering': {
        'percent': None,
        'servo_pos': None,
    },
    'throttle': {
        'percent': None,
    },
    'motor': {
        'speed_pwm': None,
        'direction': None,
    },
    'battery': {
        'voltage': None,
        'percent': None,
        'warn': None,
    },
    'status': {
        'state': None,
        'info': None,
        'heartbeat': None,
    },
    'raw': {}
}

TOPIC_MAP = {
    'rccar/status/state': ('status', 'state', str),
    'rccar/status/info': ('status', 'info', str),
    'rccar/status/heartbeat': ('status', 'heartbeat', int),
    'rccar/status/rc': ('rc', 'status', str),
    'rccar/status/signal': ('rc', 'signal', int),
    'rccar/rc/ch1_us': ('rc', 'ch1_us', int),
    'rccar/rc/ch2_us': ('rc', 'ch2_us', int),
    'rccar/steering/percent': ('steering', 'percent', int),
    'rccar/steering/servo_pos': ('steering', 'servo_pos', int),
    'rccar/throttle/percent': ('throttle', 'percent', int),
    'rccar/motor/speed_pwm': ('motor', 'speed_pwm', int),
    'rccar/motor/direction': ('motor', 'direction', str),
    'rccar/battery/voltage': ('battery', 'voltage', float),
    'rccar/battery/percent': ('battery', 'percent', int),
    'rccar/battery/warn': ('battery', 'warn', str),
}


def cast_value(raw, caster):
    if caster is int:
        return int(float(raw))
    if caster is float:
        return float(raw)
    return raw


def discover_serial_port():
    candidates = []
    for port in serial.tools.list_ports.comports():
        desc = f"{port.device} {port.description} {port.hwid}".lower()
        if any(key in desc for key in ['arduino', 'acm', 'usb serial', 'ch340', 'cp210']):
            candidates.append(port.device)
    if candidates:
        return candidates[0]
    return SERIAL_PORT


def open_serial():
    port = discover_serial_port() if DISCOVERY_ENABLED else SERIAL_PORT
    logger.info('Opening serial port %s at %s baud', port, SERIAL_BAUD)
    return serial.Serial(port, SERIAL_BAUD, timeout=SERIAL_TIMEOUT)


def build_payload():
    payload = json.loads(json.dumps(state))
    payload['timestamp'] = datetime.now(timezone.utc).isoformat()
    return payload


def update_state(topic, raw_value):
    state['raw'][topic] = raw_value
    mapping = TOPIC_MAP.get(topic)
    if not mapping:
        return False
    section, key, caster = mapping
    try:
        state[section][key] = cast_value(raw_value, caster)
    except Exception:
        logger.warning('Failed to cast %s=%r', topic, raw_value)
        return False
    return True


def on_connect(client, userdata, flags, reason_code, properties=None):
    logger.info('Connected to MQTT broker %s:%s rc=%s', MQTT_BROKER, MQTT_PORT, reason_code)


def main():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, client_id='rc-car-serial-mqtt')
    client.on_connect = on_connect
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()

    ser = None
    last_publish = 0.0

    while True:
        try:
            if ser is None or not ser.is_open:
                ser = open_serial()
                try:
                    ser.reset_input_buffer()
                except Exception:
                    pass

            line = ser.readline().decode('utf-8', errors='replace').strip()
            if not line:
                if time.time() - last_publish >= max(PUBLISH_INTERVAL, 1.0):
                    client.publish(f'{MQTT_BASE_TOPIC}/bridge/status', json.dumps({
                        'state': 'idle',
                        'timestamp': datetime.now(timezone.utc).isoformat(),
                        'host': socket.gethostname()
                    }), qos=0, retain=False)
                    last_publish = time.time()
                continue

            parts = line.split(' ', 1)
            if len(parts) != 2:
                logger.info('Ignoring malformed serial line: %s', line)
                continue

            topic, raw_value = parts[0].strip(), parts[1].strip()
            updated = update_state(topic, raw_value)
            client.publish(f'{MQTT_BASE_TOPIC}/raw/{topic}', raw_value, qos=0, retain=False)

            if updated and (time.time() - last_publish >= PUBLISH_INTERVAL or topic in ('rccar/battery/voltage', 'rccar/status/signal')):
                payload = build_payload()
                client.publish(MQTT_JSON_TOPIC, json.dumps(payload), qos=0, retain=False)
                last_publish = time.time()

        except serial.SerialException as exc:
            logger.error('Serial error: %s', exc)
            if ser is not None:
                try:
                    ser.close()
                except Exception:
                    pass
                ser = None
            time.sleep(2)
        except KeyboardInterrupt:
            break
        except Exception as exc:
            logger.exception('Unexpected error: %s', exc)
            time.sleep(1)

    if ser is not None and ser.is_open:
        ser.close()
    client.loop_stop()
    client.disconnect()


if __name__ == '__main__':
    main()