import json
import time
import threading
import subprocess
from flask import Flask, jsonify, render_template
import paho.mqtt.client as mqtt

MQTT_BROKER = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "sensors/position"

WEB_HOST = "0.0.0.0"
WEB_PORT = 5000

STALE_AFTER_SECONDS = 3.0

latest_position = {
    "x": None,
    "y": None,
    "ts": None,
    "received_at": None,
    "last_update_unix": None
}
data_lock = threading.Lock()

app = Flask(__name__)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe(MQTT_TOPIC)
        print(f"Subscribed to {MQTT_TOPIC}")
    else:
        print(f"Failed to connect to MQTT broker, code={rc}")

def on_message(client, userdata, msg):
    global latest_position

    try:
        payload = json.loads(msg.payload.decode("utf-8"))
    except Exception as e:
        print("Invalid MQTT payload:", e)
        return

    x = payload.get("x")
    y = payload.get("y")
    ts = payload.get("ts")

    with data_lock:
        latest_position["x"] = x
        latest_position["y"] = y
        latest_position["ts"] = ts
        latest_position["received_at"] = time.strftime("%Y-%m-%d %H:%M:%S")
        latest_position["last_update_unix"] = time.time()

    print("Updated position:", latest_position)

mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message
mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
mqtt_client.loop_start()

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/api/position")
def api_position():
    with data_lock:
        data = dict(latest_position)

    now = time.time()
    last_update = data.get("last_update_unix")

    if last_update is None:
        data["state"] = "no_data"
        data["message"] = "No valid position data received yet."
    elif now - last_update > STALE_AFTER_SECONDS:
        data["state"] = "stale"
        data["message"] = "Position data is stale."
    else:
        data["state"] = "ok"
        data["message"] = "Live position data received."

    return jsonify(data)

@app.route("/status")
def service_status():
    services = [
        "web-visu.service",
        "uwb-mqtt.service",
        "mosquitto.service",
    ]

    data = []
    for svc in services:
        try:
            result = subprocess.run(
                ["systemctl", "is-active", svc],
                capture_output=True,
                text=True,
                check=False
            )
            active = result.stdout.strip()

            error_log = ""
            if active != "active":
                log_result = subprocess.run(
                    ["journalctl", "-u", svc, "--no-pager", "-n", "10"],
                    capture_output=True,
                    text=True,
                    check=False
                )
                error_log = log_result.stdout.strip()
        except Exception as e:
            active = "unknown"
            error_log = f"Error checking service: {e}"

        data.append({
            "name": svc,
            "status": active,
            "error_log": error_log
        })

    return render_template("status.html", services=data)

if __name__ == "__main__":
    app.run(host=WEB_HOST, port=WEB_PORT, debug=False)