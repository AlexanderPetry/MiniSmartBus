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

# Wake up and enable logging
dwm.write(b"\r\r")
time.sleep(1)
dwm.write(b"lec\r")
time.sleep(1)

last_any_serial = time.time()
last_valid_pos = None

try:
    while True:
        raw = dwm.readline()

        if not raw:
            if time.time() - last_any_serial > 5:
                print("No serial data received for 5 seconds")
                last_any_serial = time.time()
            continue

        last_any_serial = time.time()

        # Decode and clean up
        try:
            line = raw.decode("utf-8", errors="ignore").strip()
        except Exception as e:
            print("Decode failed:", e)
            continue

        if not line:
            continue

        print("RAW:", repr(line))

        # Skip anything that cannot be a DWM1001 log line
        if not (line.startswith("DIST") or "POS" in line):
            continue

        parts = [p.strip() for p in line.split(",")]

        if "POS" not in parts:
            continue

        pos_index = -1
        for i, p in enumerate(parts):
            if p == "POS":
                pos_index = i
                break

        if pos_index == -1:
            continue

        # Attempt to read POS,x,y (even if there is extra junk after)
        try:
            x = float(parts[pos_index + 1])
            y = float(parts[pos_index + 2])

            pos = {
                "x": x,
                "y": y,
                "ts": time.time()
            }

            payload = json.dumps(pos)
            print("Publishing:", payload)

            result = client.publish(MQTT_TOPIC, payload, qos=0)
            result.wait_for_publish()
            last_valid_pos = time.time()

        except (ValueError, IndexError) as e:
            print("Failed to parse POS data:", e)
            print("Bad line was:", repr(line))
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