import time
from pathlib import Path

import cv2
import rclpy
from rclpy.node import Node
from rclpy.executors import ExternalShutdownException
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from ultralytics import YOLO


class ObjectDetectionNode(Node):
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

    def __init__(self):
        super().__init__('object_detection_node')

        self.declare_parameter('image_topic', '/camera/image_raw')
        self.declare_parameter('overlay_topic', '/camera/detections/image')
        self.declare_parameter('model_path', 'models/yolov8n.pt')
        self.declare_parameter('show_window', False)

        image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        overlay_topic = self.get_parameter('overlay_topic').get_parameter_value().string_value
        model_path = self.get_parameter('model_path').get_parameter_value().string_value
        self.show_window = self.get_parameter('show_window').get_parameter_value().bool_value

        self.bridge = CvBridge()
        self.model = YOLO(str(Path(model_path).expanduser()))
        self.frame_count = 0

        self.overlay_pub = self.create_publisher(Image, overlay_topic, 10)

        self.subscription = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        self.get_logger().info(f'Subscribed to image topic: {image_topic}')
        self.get_logger().info(f'Publishing overlay topic: {overlay_topic}')
        self.get_logger().info(f'Loaded YOLO model: {model_path}')

    def image_callback(self, msg: Image):
        try:
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f'Failed to convert image: {e}')
            return

        start_time = time.time()
        results = self.model(frame, conf=self.YOLO_CONF, verbose=False)
        result = results[0]
        inference_ms = (time.time() - start_time) * 1000.0

        filtered_objects = []
        names = result.names

        if result.boxes is not None:
            for box in result.boxes:
                cls_id = int(box.cls[0].item())
                cls_name = names[cls_id]
                conf = float(box.conf[0].item())

                if cls_name not in self.ALLOWED_CLASSES:
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

        self.get_logger().info(
            f'Frame {self.frame_count}: '
            f'{len(filtered_objects)} allowed detections, '
            f'inference={inference_ms:.1f} ms, '
            f'objects={filtered_objects}'
        )

        try:
            overlay_msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
            overlay_msg.header = msg.header
            self.overlay_pub.publish(overlay_msg)
        except Exception as e:
            self.get_logger().error(f'Failed to publish overlay image: {e}')

        if self.show_window:
            cv2.imshow("detections", frame)
            cv2.waitKey(1)

        self.frame_count += 1


def main(args=None):
    object_detection_node = None
    try:
        rclpy.init(args=args)
        object_detection_node = ObjectDetectionNode()
        rclpy.spin(object_detection_node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        try:
            if object_detection_node is not None:
                object_detection_node.destroy_node()
        except Exception:
            pass
        cv2.destroyAllWindows()
        rclpy.shutdown()


if __name__ == '__main__':
    main()