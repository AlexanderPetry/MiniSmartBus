import io
from threading import Condition
from flask import Flask, Response
from picamera2 import Picamera2
from picamera2.encoders import JpegEncoder
from picamera2.outputs import FileOutput

app = Flask(__name__)

class StreamingOutput(io.BufferedIOBase):
    def __init__(self):
        self.frame = None
        self.condition = Condition()

    def write(self, buf):
        with self.condition:
            self.frame = buf
            self.condition.notify_all()

output = StreamingOutput()

picam2 = Picamera2()
picam2.configure(
    picam2.create_video_configuration(
        main={"size": (640, 480)}
    )
)
picam2.start_recording(JpegEncoder(), FileOutput(output))

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

@app.route("/health")
def health():
    return "ok", 200

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5001, debug=False, threaded=True)