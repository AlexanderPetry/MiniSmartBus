# drive_mode_arbiter.py

import copy
import time

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

from py_bus_interfaces.msg import DriverCommand


class DriveModeArbiterNode(Node):
    def __init__(self):
        super().__init__('drive_mode_arbiter')

        self.declare_parameter('manual_topic', '/manual_cmd')
        self.declare_parameter('auto_topic', '/auto_cmd')
        self.declare_parameter('mode_topic', '/drive_mode')
        self.declare_parameter('output_topic', '/esp32_cmd')
        self.declare_parameter('default_mode', 'manual')
        self.declare_parameter('command_timeout_sec', 0.5)
        self.declare_parameter('publish_rate_hz', 20.0)
        self.declare_parameter('publish_debug', True)

        self.manual_topic = str(self.get_parameter('manual_topic').value)
        self.auto_topic = str(self.get_parameter('auto_topic').value)
        self.mode_topic = str(self.get_parameter('mode_topic').value)
        self.output_topic = str(self.get_parameter('output_topic').value)
        self.mode = str(self.get_parameter('default_mode').value).strip().lower()
        self.command_timeout_sec = float(self.get_parameter('command_timeout_sec').value)
        self.publish_rate_hz = float(self.get_parameter('publish_rate_hz').value)
        self.publish_debug = bool(self.get_parameter('publish_debug').value)

        self.manual_cmd = None
        self.auto_cmd = None
        self.manual_stamp = 0.0
        self.auto_stamp = 0.0
        self.last_output = None

        self.pub = self.create_publisher(DriverCommand, self.output_topic, 10)

        self.manual_sub = self.create_subscription(
            DriverCommand,
            self.manual_topic,
            self.manual_callback,
            10
        )

        self.auto_sub = self.create_subscription(
            DriverCommand,
            self.auto_topic,
            self.auto_callback,
            10
        )

        self.mode_sub = self.create_subscription(
            String,
            self.mode_topic,
            self.mode_callback,
            10
        )

        period = 1.0 / max(self.publish_rate_hz, 1.0)
        self.timer = self.create_timer(period, self.timer_callback)

        self.get_logger().info(
            f'drive_mode_arbiter started | mode={self.mode} | '
            f'manual={self.manual_topic} auto={self.auto_topic} output={self.output_topic}'
        )

    def manual_callback(self, msg: DriverCommand):
        self.manual_cmd = copy.deepcopy(msg)
        self.manual_stamp = time.monotonic()

    def auto_callback(self, msg: DriverCommand):
        self.auto_cmd = copy.deepcopy(msg)
        self.auto_stamp = time.monotonic()

    def mode_callback(self, msg: String):
        requested = msg.data.strip().lower()

        aliases = {
            'manual': 'manual',
            'man': 'manual',
            'm': 'manual',
            'auto': 'auto',
            'automatic': 'auto',
            'autonomous': 'auto',
            'guided': 'auto',
            'auto_guided': 'auto',
            'nav': 'auto'
        }

        normalized = aliases.get(requested)
        if normalized is None:
            self.get_logger().warning(f'Ignoring unknown drive mode: {requested}')
            return

        if normalized != self.mode:
            self.mode = normalized
            self.get_logger().info(f'Drive mode changed to: {self.mode}')

    def is_fresh(self, stamp: float) -> bool:
        if stamp <= 0.0:
            return False
        return (time.monotonic() - stamp) <= self.command_timeout_sec

    def make_stop_cmd(self) -> DriverCommand:
        msg = DriverCommand()
        msg.speed_kmh = 0.0
        msg.steering_deg = 0.0
        return msg

    def timer_callback(self):
        selected = None
        source = 'none'

        if self.mode == 'manual':
            if self.is_fresh(self.manual_stamp) and self.manual_cmd is not None:
                selected = copy.deepcopy(self.manual_cmd)
                source = 'manual'
        elif self.mode == 'auto':
            if self.is_fresh(self.auto_stamp) and self.auto_cmd is not None:
                selected = copy.deepcopy(self.auto_cmd)
                source = 'auto'

        if selected is None:
            selected = self.make_stop_cmd()
            source = 'timeout_stop'

        self.pub.publish(selected)

        changed = (
            self.last_output is None or
            abs(self.last_output.speed_kmh - selected.speed_kmh) > 1e-6 or
            abs(self.last_output.steering_deg - selected.steering_deg) > 1e-6
        )

        if changed and self.publish_debug:
            self.get_logger().info(
                f'arbiter -> esp32_cmd | mode={self.mode} source={source} '
                f'speed={selected.speed_kmh:.2f} km/h steer={selected.steering_deg:.2f} deg'
            )

        self.last_output = copy.deepcopy(selected)


def main(args=None):
    rclpy.init(args=args)
    node = DriveModeArbiterNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
