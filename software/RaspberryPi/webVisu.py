import json
import time
import threading
import subprocess
import requests
from flask import Flask, jsonify, render_template, Response, stream_with_context
import paho.mqtt.client as mqtt

MQTT_BROKER = "localhost"
MQTT_PORT = 1883

POSITION_TOPIC = "sensors/position"
MPU_TOPIC = "minismartbus/sensors/mpu6050"
RC_CAR_TOPIC = "minismartbus/rc_car/state"

WEB_HOST = "0.0.0.0"
WEB_PORT = 5000

CAMERA_STREAM_URL = "http://127.0.0.1:5001/video_feed"

STALE_AFTER_SECONDS = 3.0

latest_position = {
    "x": None,
    "y": None,
    "ts": None,
    "received_at": None,
    "last_update_unix": None
}

latest_mpu = {
    "timestamp": None,
    "host": None,
    "sensor": None,
    "i2c_bus": None,
    "i2c_address": None,
    "accel_g": {"x": None, "y": None, "z": None},
    "gyro_dps": {"x": None, "y": None, "z": None},
    "temperature_c": None,
    "raw": {},
    "received_at": None,
    "last_update_unix": None
}

latest_rc_car = {
    "timestamp": None,
    "host": None,
    "source": None,
    "rc": {
        "signal": None,
        "status": None,
        "ch1_us": None,
        "ch2_us": None
    },
    "steering": {
        "percent": None,
        "servo_pos": None
    },
    "throttle": {
        "percent": None
    },
    "motor": {
        "speed_pwm": None,
        "direction": None
    },
    "battery": {
        "voltage": None,
        "percent": None,
        "warn": None
    },
    "status": {
        "state": None,
        "info": None,
        "heartbeat": None
    },
    "raw": {},
    "received_at": None,
    "last_update_unix": None
}

data_lock = threading.Lock()

app = Flask(__name__)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe([
            (POSITION_TOPIC, 0),
            (MPU_TOPIC, 0),
            (RC_CAR_TOPIC, 0),
        ])
        print(f"Subscribed to {POSITION_TOPIC}")
        print(f"Subscribed to {MPU_TOPIC}")
        print(f"Subscribed to {RC_CAR_TOPIC}")
    else:
        print(f"Failed to connect to MQTT broker, code={rc}")

def on_message(client, userdata, msg):
    global latest_position, latest_mpu, latest_rc_car

    try:
        payload = json.loads(msg.payload.decode("utf-8"))
    except Exception as e:
        print(f"Invalid MQTT payload on topic {msg.topic}: {e}")
        return

    with data_lock:
        if msg.topic == POSITION_TOPIC:
            latest_position["x"] = payload.get("x")
            latest_position["y"] = payload.get("y")
            latest_position["ts"] = payload.get("ts")
            latest_position["received_at"] = time.strftime("%Y-%m-%d %H:%M:%S")
            latest_position["last_update_unix"] = time.time()
            print("Updated position:", latest_position)

        elif msg.topic == MPU_TOPIC:
            latest_mpu["timestamp"] = payload.get("timestamp")
            latest_mpu["host"] = payload.get("host")
            latest_mpu["sensor"] = payload.get("sensor")
            latest_mpu["i2c_bus"] = payload.get("i2c_bus")
            latest_mpu["i2c_address"] = payload.get("i2c_address")
            latest_mpu["accel_g"] = payload.get("accel_g", {"x": None, "y": None, "z": None})
            latest_mpu["gyro_dps"] = payload.get("gyro_dps", {"x": None, "y": None, "z": None})
            latest_mpu["temperature_c"] = payload.get("temperature_c")
            latest_mpu["raw"] = payload.get("raw", {})
            latest_mpu["received_at"] = time.strftime("%Y-%m-%d %H:%M:%S")
            latest_mpu["last_update_unix"] = time.time()
            print("Updated MPU:", latest_mpu)

        elif msg.topic == RC_CAR_TOPIC:
            latest_rc_car["timestamp"] = payload.get("timestamp")
            latest_rc_car["host"] = payload.get("host")
            latest_rc_car["source"] = payload.get("source")
            latest_rc_car["rc"] = payload.get("rc", {})
            latest_rc_car["steering"] = payload.get("steering", {})
            latest_rc_car["throttle"] = payload.get("throttle", {})
            latest_rc_car["motor"] = payload.get("motor", {})
            latest_rc_car["battery"] = payload.get("battery", {})
            latest_rc_car["status"] = payload.get("status", {})
            latest_rc_car["raw"] = payload.get("raw", {})
            latest_rc_car["received_at"] = time.strftime("%Y-%m-%d %H:%M:%S")
            latest_rc_car["last_update_unix"] = time.time()
            print("Updated RC Car:", latest_rc_car)

        else:
            print(f"Ignoring message from unexpected topic: {msg.topic}")

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

@app.route("/api/mpu")
def api_mpu():
    with data_lock:
        data = json.loads(json.dumps(latest_mpu))

    now = time.time()
    last_update = data.get("last_update_unix")

    if last_update is None:
        data["state"] = "no_data"
        data["message"] = "No valid MPU data received yet."
    elif now - last_update > STALE_AFTER_SECONDS:
        data["state"] = "stale"
        data["message"] = "MPU data is stale."
    else:
        data["state"] = "ok"
        data["message"] = "Live MPU data received."

    return jsonify(data)

@app.route("/api/rc_car")
def api_rc_car():
    with data_lock:
        data = json.loads(json.dumps(latest_rc_car))

    now = time.time()
    last_update = data.get("last_update_unix")

    if last_update is None:
        data["state"] = "no_data"
        data["message"] = "No valid RC car data received yet."
    elif now - last_update > STALE_AFTER_SECONDS:
        data["state"] = "stale"
        data["message"] = "RC car data is stale."
    else:
        data["state"] = "ok"
        data["message"] = "Live RC car data received."

    return jsonify(data)

@app.route("/camera_feed")
def camera_feed():
    upstream = requests.get(CAMERA_STREAM_URL, stream=True, timeout=10)
    return Response(
        stream_with_context(upstream.iter_content(chunk_size=1024)),
        content_type=upstream.headers.get(
            "Content-Type",
            "multipart/x-mixed-replace; boundary=frame"
        )
    )

@app.route("/status")
def service_status():
    services = [
        "web-visu.service",
        "uwb-mqtt.service",
        "camera-stream.service",
        "mpu-mqtt.service",
        "base-frame-mqtt.service",
        "mosquitto.service",
        "actions.runner.AlexanderPetry-MiniSmartBus.minibus.service"
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