# Libraries used:
# pyserial     -> pip install pyserial
# paho-mqtt   -> pip install paho-mqtt
# json        -> built into Python, no pip install needed
# time        -> built into Python, no pip install needed

import json
import time
import serial
import paho.mqtt.client as mqtt

SERIAL_PORT = "/dev/ttyACM0"
BAUD_RATE = 115200

MQTT_BROKER = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "sensors/position"

client = mqtt.Client()
client.connect(MQTT_BROKER, MQTT_PORT, 60)
client.loop_start()

dwm = serial.Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=1)
print("Connected to", dwm.name)

dwm.write(b"\r\r")
time.sleep(1)
dwm.write(b"lec\r")
time.sleep(1)

try:
    while True:
        raw = dwm.readline()

        if not raw:
            continue

        try:
            line = raw.decode("utf-8", errors="ignore").strip()
        except Exception:
            continue

        if not line:
            continue

        print("RAW:", line)

        if "POS" not in line:
            continue

        parts = line.split(",")

        if "POS" in parts:
            try:
                pos_index = parts.index("POS")
                pos = {
                    "x": float(parts[pos_index + 1]),
                    "y": float(parts[pos_index + 2]),
                    "ts": time.time()
                }

                payload = json.dumps(pos)
                print("Publishing:", payload)

                result = client.publish(MQTT_TOPIC, payload, qos=0)
                result.wait_for_publish()

            except (ValueError, IndexError) as e:
                print("Failed to parse POS data:", e)
                continue

except KeyboardInterrupt:
    print("Stopping...")

finally:
    try:
        dwm.write(b"\r")
    except Exception:
        pass

    dwm.close()
    client.loop_stop()
    client.disconnect()
    print("Closed serial and MQTT connection.")