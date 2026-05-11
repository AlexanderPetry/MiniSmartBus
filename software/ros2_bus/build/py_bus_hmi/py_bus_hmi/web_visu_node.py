import os
import cv2
import copy
import threading

import rclpy
from rclpy.node import Node
from rclpy.executors import ExternalShutdownException

from flask import Flask, jsonify, send_from_directory, Response, request

from sensor_msgs.msg import Image
from std_msgs.msg import String
from nav_msgs.msg import OccupancyGrid
from cv_bridge import CvBridge
from py_bus_interfaces.msg import ImuData, UwbData, DriverCommand, DriverStatus


class WebVisuNode(Node):
    def __init__(self):
        super().__init__('web_visu_node')

        self.latest_imu = {
            'sample_id': None,
            'accel_x': None,
            'accel_y': None,
            'accel_z': None,
            'gyro_x': None,
            'gyro_y': None,
            'gyro_z': None,
            'temp': None,
        }

        self.latest_uwb = {
            'x': None,
            'y': None,
            'ts': None,
        }

        self.latest_driver = {
            'source': None,
            'rc_steering_us': None,
            'rc_throttle_us': None,
            'commanded_speed_kmh': None,
            'commanded_steering_deg': None,
            'applied_speed_kmh': None,
            'applied_steering_deg': None,
            'raw_line': None,
            'stamp_sec': None,
            'stamp_nanosec': None,
        }

        self.last_command = {
            'speed_kmh': 0.0,
            'steering_deg': 0.0,
        }

        self.drive_mode = 'manual'

        self.latest_frame = None
        self.frame_lock = threading.Lock()
        self.bridge = CvBridge()

        self.map_lock = threading.Lock()
        self.base_map_msg = None
        self.obstacles = []

        self.driver_command_publisher = self.create_publisher(
            DriverCommand,
            'manual_cmd',
            10
        )

        self.drive_mode_publisher = self.create_publisher(
            String,
            'drive_mode',
            10
        )

        self.test_map_publisher = self.create_publisher(
            OccupancyGrid,
            '/map_test',
            10
        )

        self.create_subscription(
            ImuData,
            'imu_data',
            self.imu_callback,
            10
        )

        self.create_subscription(
            UwbData,
            'uwb_data',
            self.uwb_callback,
            10
        )

        self.create_subscription(
            DriverStatus,
            'esp32_status',
            self.driver_callback,
            10
        )

        self.create_subscription(
            Image,
            '/camera/detections/image',
            self.image_callback,
            10
        )

        self.create_subscription(
            OccupancyGrid,
            '/map',
            self.map_callback,
            10
        )

        web_dir = os.path.join(os.path.dirname(__file__), 'web')
        self.app = Flask(__name__, static_folder=web_dir, static_url_path='')

        self.setup_routes()

        self.flask_thread = threading.Thread(
            target=self.run_flask,
            daemon=True
        )
        self.flask_thread.start()

        self.get_logger().info('HMI running at http://0.0.0.0:8000')
        self.get_logger().info('Obstacle test map will be published on /map_test')

    def imu_callback(self, msg):
        self.latest_imu = {
            'sample_id': msg.sample_id,
            'accel_x': msg.accel_x,
            'accel_y': msg.accel_y,
            'accel_z': msg.accel_z,
            'gyro_x': msg.gyro_x,
            'gyro_y': msg.gyro_y,
            'gyro_z': msg.gyro_z,
            'temp': msg.temp,
        }

    def uwb_callback(self, msg):
        self.latest_uwb = {
            'x': msg.x,
            'y': msg.y,
            'ts': msg.ts,
        }

    def driver_callback(self, msg):
        self.latest_driver = {
            'source': msg.source,
            'rc_steering_us': msg.rc_steering_us,
            'rc_throttle_us': msg.rc_throttle_us,
            'commanded_speed_kmh': msg.commanded_speed_kmh,
            'commanded_steering_deg': msg.commanded_steering_deg,
            'applied_speed_kmh': msg.applied_speed_kmh,
            'applied_steering_deg': msg.applied_steering_deg,
            'raw_line': msg.raw_line,
            'stamp_sec': msg.stamp.sec,
            'stamp_nanosec': msg.stamp.nanosec,
        }

    def image_callback(self, msg):
        try:
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            ok, buffer = cv2.imencode('.jpg', frame)
            if ok:
                with self.frame_lock:
                    self.latest_frame = buffer.tobytes()
        except Exception as e:
            self.get_logger().error(f'Failed to process overlay image: {e}')

    def map_callback(self, msg):
        with self.map_lock:
            self.base_map_msg = msg
        self.publish_test_map()

    def mjpeg_generator(self):
        while True:
            with self.frame_lock:
                frame = self.latest_frame

            if frame is None:
                continue

            yield (
                b'--frame\r\n'
                b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n'
            )

    def publish_driver_command(self, speed_kmh, steering_deg):
        speed_kmh = max(-4.0, min(4.0, float(speed_kmh)))
        steering_deg = max(-35.0, min(35.0, float(steering_deg)))

        msg = DriverCommand()
        msg.speed_kmh = speed_kmh
        msg.steering_deg = steering_deg

        self.driver_command_publisher.publish(msg)

        self.last_command = {
            'speed_kmh': speed_kmh,
            'steering_deg': steering_deg,
        }

        self.get_logger().info(
            f'Web manual command published: speed={speed_kmh:.2f} km/h, '
            f'steering={steering_deg:.2f} deg'
        )

    def publish_drive_mode(self, mode):
        mode = str(mode).strip().lower()

        if mode not in ('manual', 'auto'):
            raise ValueError('mode must be manual or auto')

        msg = String()
        msg.data = mode
        self.drive_mode_publisher.publish(msg)
        self.drive_mode = mode

        self.get_logger().info(f'Web drive mode published: {mode}')

    def clamp_rect_to_map(self, rect, width, height):
        x1 = int(max(0, min(width - 1, rect.get('x1', 0))))
        y1 = int(max(0, min(height - 1, rect.get('y1', 0))))
        x2 = int(max(0, min(width - 1, rect.get('x2', 0))))
        y2 = int(max(0, min(height - 1, rect.get('y2', 0))))

        return {
            'id': rect.get('id'),
            'x1': min(x1, x2),
            'y1': min(y1, y2),
            'x2': max(x1, x2),
            'y2': max(y1, y2),
        }

    def build_test_map(self):
        with self.map_lock:
            if self.base_map_msg is None:
                return None

            base = self.base_map_msg
            obstacles = list(self.obstacles)

        test_map = OccupancyGrid()
        test_map.header.stamp = self.get_clock().now().to_msg()
        test_map.header.frame_id = base.header.frame_id
        test_map.info = copy.deepcopy(base.info)
        data = list(base.data)

        width = base.info.width
        height = base.info.height

        for rect in obstacles:
            r = self.clamp_rect_to_map(rect, width, height)

            for py in range(r['y1'], r['y2'] + 1):
                for px in range(r['x1'], r['x2'] + 1):
                    map_y = height - 1 - py
                    idx = px + map_y * width
                    if 0 <= idx < len(data):
                        data[idx] = 100

        test_map.data = data
        return test_map

    def publish_test_map(self):
        test_map = self.build_test_map()
        if test_map is None:
            return
        self.test_map_publisher.publish(test_map)

    def setup_routes(self):
        node = self
        app = self.app
        web_dir = app.static_folder

        @app.route('/')
        def index():
            return send_from_directory(web_dir, 'index.html')

        @app.route('/style.css')
        def style():
            return send_from_directory(web_dir, 'style.css')

        @app.route('/app.js')
        def script():
            return send_from_directory(web_dir, 'app.js')

        @app.route('/api/data')
        def data():
            return jsonify({
                'imu': node.latest_imu,
                'uwb': node.latest_uwb,
                'driver': node.latest_driver,
                'last_command': node.last_command,
                'drive_mode': node.drive_mode,
            })

        @app.route('/api/driver_command', methods=['POST'])
        def driver_command():
            payload = request.get_json(silent=True) or {}

            try:
                speed_kmh = float(payload.get('speed_kmh', 0.0))
                steering_deg = float(payload.get('steering_deg', 0.0))
            except (TypeError, ValueError):
                return jsonify({
                    'ok': False,
                    'error': 'invalid speed_kmh or steering_deg'
                }), 400

            node.publish_driver_command(speed_kmh, steering_deg)

            return jsonify({
                'ok': True,
                'sent': {
                    'speed_kmh': node.last_command['speed_kmh'],
                    'steering_deg': node.last_command['steering_deg'],
                },
                'drive_mode': node.drive_mode,
            })

        @app.route('/api/drive_mode', methods=['POST'])
        def drive_mode():
            payload = request.get_json(silent=True) or {}
            mode = str(payload.get('mode', '')).strip().lower()

            if mode not in ('manual', 'auto'):
                return jsonify({
                    'ok': False,
                    'error': 'mode must be manual or auto'
                }), 400

            try:
                node.publish_drive_mode(mode)
            except Exception as e:
                return jsonify({
                    'ok': False,
                    'error': str(e)
                }), 500

            return jsonify({
                'ok': True,
                'mode': node.drive_mode,
            })

        @app.route('/api/obstacles', methods=['GET'])
        def get_obstacles():
            with node.map_lock:
                base_map_ready = node.base_map_msg is not None
                obstacles = list(node.obstacles)

            return jsonify({
                'ok': True,
                'map_ready': base_map_ready,
                'topic': '/map_test',
                'obstacles': obstacles,
            })

        @app.route('/api/obstacles', methods=['POST'])
        def set_obstacles():
            payload = request.get_json(silent=True) or {}
            incoming = payload.get('obstacles', [])

            if not isinstance(incoming, list):
                return jsonify({
                    'ok': False,
                    'error': 'obstacles must be a list'
                }), 400

            with node.map_lock:
                if node.base_map_msg is None:
                    return jsonify({
                        'ok': False,
                        'error': 'base map not received yet'
                    }), 409

                width = node.base_map_msg.info.width
                height = node.base_map_msg.info.height

                cleaned = []
                for item in incoming:
                    if not isinstance(item, dict):
                        continue
                    cleaned.append(node.clamp_rect_to_map(item, width, height))

                node.obstacles = cleaned

            node.publish_test_map()

            return jsonify({
                'ok': True,
                'count': len(cleaned),
                'topic': '/map_test',
            })

        @app.route('/api/obstacles', methods=['DELETE'])
        def clear_obstacles():
            with node.map_lock:
                node.obstacles = []

            node.publish_test_map()

            return jsonify({
                'ok': True,
                'count': 0,
                'topic': '/map_test',
            })

        @app.route('/video_feed')
        def video_feed():
            return Response(
                node.mjpeg_generator(),
                mimetype='multipart/x-mixed-replace; boundary=frame'
            )

        @app.route('/navigation')
        def navigation():
            return send_from_directory(web_dir, 'navigation.html')

        @app.route('/navigation.js')
        def navigation_script():
            return send_from_directory(web_dir, 'navigation.js')

    def run_flask(self):
        self.app.run(
            host='0.0.0.0',
            port=8000,
            debug=False,
            use_reloader=False,
            threaded=True
        )


def main(args=None):
    web_visu_node = None
    try:
        rclpy.init(args=args)
        web_visu_node = WebVisuNode()
        rclpy.spin(web_visu_node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        if web_visu_node is not None:
            web_visu_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
