# Libraries used:
# flask       -> pip install flask
# paho-mqtt   -> pip install paho-mqtt
# json        -> built into Python, no pip install needed
# threading   -> built into Python, no pip install needed
# time        -> built into Python, no pip install needed

import json
import time
import threading
from flask import Flask, jsonify, render_template
import paho.mqtt.client as mqtt

MQTT_BROKER = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "sensors/position"

WEB_HOST = "0.0.0.0"
WEB_PORT = 5000

latest_position = {
    "x": None,
    "y": None,
    "ts": None,
    "received_at": None
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

    with data_lock:
        latest_position["x"] = payload.get("x")
        latest_position["y"] = payload.get("y")
        latest_position["ts"] = payload.get("ts")
        latest_position["received_at"] = time.strftime("%Y-%m-%d %H:%M:%S")

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
        return jsonify(latest_position)

if __name__ == "__main__":
    app.run(host=WEB_HOST, port=WEB_PORT, debug=False)




import subprocess

@app.route("/status")
def service_status():
    services = [
        "position-web.service",
        "minibus.service",
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
        except Exception:
            active = "unknown"

        data.append({"name": svc, "status": active})

    return render_template("status.html", services=data)