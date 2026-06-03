import time
import serial
import rclpy
from rclpy.node import Node
from rclpy.executors import ExternalShutdownException

from py_bus_interfaces.msg import UwbData


class UwbNode(Node):
    SERIAL_PORT = "/dev/ttyACM0"
    BAUD_RATE = 115200

    def __init__(self):
        super().__init__('uwb_node')
        self.publisher_ = self.create_publisher(UwbData, 'uwb_data', 10)

        self.dwm = serial.Serial(
            port=self.SERIAL_PORT,
            baudrate=self.BAUD_RATE,
            timeout=0.1
        )

        self.get_logger().info(f'Connected to {self.dwm.name}')

        self.init_dwm()

        self.last_any_serial = time.time()
        self.last_valid_pos = None

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def init_dwm(self):
        self.dwm.write(b'\r\r')
        time.sleep(1.0)
        self.dwm.write(b'lec\r')
        time.sleep(1.0)

    def read_sample(self):
        raw = self.dwm.readline()

        if not raw:
            if time.time() - self.last_any_serial > 5.0:
                self.get_logger().warn('No serial data received for 5 seconds')
                self.last_any_serial = time.time()
            return None

        self.last_any_serial = time.time()

        try:
            line = raw.decode("utf-8", errors="ignore").strip()
        except Exception as e:
            self.get_logger().warn(f'Decode failed: {e}')
            return None

        if not line:
            return None

        self.get_logger().debug(f'RAW: {repr(line)}')

        if not (line.startswith("DIST") or "POS" in line):
            return None

        parts = [p.strip() for p in line.split(",")]

        if "POS" not in parts:
            return None

        pos_index = -1
        for i, p in enumerate(parts):
            if p == "POS":
                pos_index = i
                break

        if pos_index == -1:
            return None

        try:
            x = float(parts[pos_index + 1])
            y = float(parts[pos_index + 2])

            msg = UwbData()
            msg.x = x
            msg.y = y
            msg.ts = time.time()

            self.last_valid_pos = time.time()
            return msg

        except (ValueError, IndexError) as e:
            self.get_logger().warn(f'Failed to parse POS data: {e}')
            self.get_logger().warn(f'Bad line was: {repr(line)}')
            return None

    def timer_callback(self):
        msg = self.read_sample()

        if msg is None:
            return

        self.publisher_.publish(msg)
        self.get_logger().info(
            f'Publishing UWB position: x={msg.x:.3f}, y={msg.y:.3f}, ts={msg.ts:.3f}'
        )

    def destroy_node(self):
        try:
            self.dwm.write(b'\r')
        except Exception:
            pass

        try:
            self.dwm.close()
        except Exception:
            pass

        super().destroy_node()


def main(args=None):
    uwb_node = None
    try:
        rclpy.init(args=args)
        uwb_node = UwbNode()
        rclpy.spin(uwb_node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        if uwb_node is not None:
            uwb_node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()