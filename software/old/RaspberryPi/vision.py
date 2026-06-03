import io
import time
import threading
from threading import Condition
from pathlib import Path

import cv2
from flask import Flask, Response, jsonify
from picamera2 import Picamera2
from ultralytics import YOLO

app = Flask(__name__)

PROJECT_ROOT = Path(__file__).resolve().parent
MODEL_PATH = PROJECT_ROOT / "models" / "yolov8n.pt"

FRAME_WIDTH = 640
FRAME_HEIGHT = 480
JPEG_QUALITY = 80
YOLO_MODEL_NAME = "yolov8n.pt"   # kept for reference, but not used now
YOLO_CONF = 0.35

ALLOWED_CLASSES = {
    "person",
    "bicycle",
    "motorcycle",
    "car",
    "bus",
    "truck",
    "traffic light",
    "stop sign",
    "bench"
}

class StreamingOutput:
    def __init__(self):
        self.frame = None
        self.condition = Condition()

output = StreamingOutput()

latest_detections = {
    "updated_at": None,
    "objects": []
}
detections_lock = threading.Lock()

model = YOLO(str(MODEL_PATH))
picam2 = Picamera2()

config = picam2.create_video_configuration(
    main={"size": (FRAME_WIDTH, FRAME_HEIGHT), "format": "RGB888"}
)
picam2.configure(config)
picam2.start()

def camera_loop():
    global latest_detections

    while True:
        frame = picam2.capture_array()

        results = model(frame, conf=YOLO_CONF, verbose=False)
        result = results[0]

        filtered_objects = []
        names = result.names

        if result.boxes is not None:
            for box in result.boxes:
                cls_id = int(box.cls[0].item())
                cls_name = names[cls_id]
                conf = float(box.conf[0].item())

                if cls_name not in ALLOWED_CLASSES:
                    continue

                x1, y1, x2, y2 = box.xyxy[0].tolist()
                filtered_objects.append({
                    "label": cls_name,
                    "confidence": round(conf, 3),
                    "x1": int(x1),
                    "y1": int(y1),
                    "x2": int(x2),
                    "y2": int(y2),
                    "width": int(x2 - x1),
                    "height": int(y2 - y1)
                })

                color = (0, 255, 0)
                if cls_name in {"person", "bicycle", "motorcycle"}:
                    color = (0, 200, 255)
                elif cls_name in {"bus", "truck"}:
                    color = (255, 180, 0)

                cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), color, 2)
                label_text = f"{cls_name} {conf:.2f}"
                cv2.putText(
                    frame,
                    label_text,
                    (int(x1), max(20, int(y1) - 8)),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.55,
                    color,
                    2,
                    cv2.LINE_AA
                )

        with detections_lock:
            latest_detections = {
                "updated_at": time.strftime("%Y-%m-%d %H:%M:%S"),
                "objects": filtered_objects
            }

        success, buffer = cv2.imencode(
            ".jpg",
            frame,
            [int(cv2.IMWRITE_JPEG_QUALITY), JPEG_QUALITY]
        )
        if not success:
            continue

        jpg_bytes = buffer.tobytes()

        with output.condition:
            output.frame = jpg_bytes
            output.condition.notify_all()

def generate():
    while True:
        with output.condition:
            output.condition.wait()
            frame = output.frame

        yield (
            b'--frame\r\n'
            b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n'
        )

@app.route("/video_feed")
def video_feed():
    return Response(
        generate(),
        mimetype="multipart/x-mixed-replace; boundary=frame"
    )

@app.route("/detections")
def detections():
    with detections_lock:
        return jsonify(latest_detections)

@app.route("/health")
def health():
    return "ok", 200

if __name__ == "__main__":
    thread = threading.Thread(target=camera_loop, daemon=True)
    thread.start()
    app.run(host="0.0.0.0", port=5001, debug=False, threaded=True)