# cmd_vel_to_ackermann.py

import math

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, TwistStamped

from py_bus_interfaces.msg import DriverCommand


class CmdVelToAckermannNode(Node):
    def __init__(self):
        super().__init__('cmd_vel_to_ackermann')

        self.declare_parameter('input_topic', '/cmd_vel')
        self.declare_parameter('input_type', 'twist')  # 'twist' or 'twist_stamped'
        self.declare_parameter('output_topic', '/auto_cmd')
        self.declare_parameter('wheelbase_m', 1.0)
        self.declare_parameter('max_speed_kmh', 4.0)
        self.declare_parameter('max_steering_deg', 35.0)
        self.declare_parameter('speed_scale', 1.0)
        self.declare_parameter('deadband_linear', 0.01)
        self.declare_parameter('deadband_angular', 0.01)
        self.declare_parameter('publish_debug', True)

        self.input_topic = str(self.get_parameter('input_topic').value)
        self.input_type = str(self.get_parameter('input_type').value).lower()
        self.output_topic = str(self.get_parameter('output_topic').value)
        self.wheelbase_m = float(self.get_parameter('wheelbase_m').value)
        self.max_speed_kmh = float(self.get_parameter('max_speed_kmh').value)
        self.max_steering_deg = float(self.get_parameter('max_steering_deg').value)
        self.speed_scale = float(self.get_parameter('speed_scale').value)
        self.deadband_linear = float(self.get_parameter('deadband_linear').value)
        self.deadband_angular = float(self.get_parameter('deadband_angular').value)
        self.publish_debug = bool(self.get_parameter('publish_debug').value)

        self.pub = self.create_publisher(DriverCommand, self.output_topic, 10)

        if self.input_type == 'twist_stamped':
            self.sub = self.create_subscription(
                TwistStamped,
                self.input_topic,
                self.twist_stamped_callback,
                10
            )
        else:
            self.sub = self.create_subscription(
                Twist,
                self.input_topic,
                self.twist_callback,
                10
            )

        self.get_logger().info(
            f'cmd_vel_to_ackermann listening on {self.input_topic} ({self.input_type}), '
            f'publishing DriverCommand on {self.output_topic}'
        )

    def twist_callback(self, msg: Twist):
        self.handle_cmd(msg.linear.x, msg.angular.z)

    def twist_stamped_callback(self, msg: TwistStamped):
        self.handle_cmd(msg.twist.linear.x, msg.twist.angular.z)

    def handle_cmd(self, linear_x: float, angular_z: float):
        v = float(linear_x)
        omega = float(angular_z)

        if abs(v) < self.deadband_linear:
            v = 0.0
        if abs(omega) < self.deadband_angular:
            omega = 0.0

        speed_kmh = v * 3.6 * self.speed_scale

        if abs(v) < 1e-6:
            steering_deg = 0.0
        else:
            steering_rad = math.atan((self.wheelbase_m * omega) / v)
            steering_deg = math.degrees(steering_rad)

        speed_kmh = max(-self.max_speed_kmh, min(self.max_speed_kmh, speed_kmh))
        steering_deg = max(-self.max_steering_deg, min(self.max_steering_deg, steering_deg))

        out = DriverCommand()
        out.speed_kmh = speed_kmh
        out.steering_deg = steering_deg
        self.pub.publish(out)

        if self.publish_debug:
            self.get_logger().info(
                f'cmd_vel -> auto_cmd | v={v:.3f} m/s omega={omega:.3f} rad/s '
                f'=> speed={speed_kmh:.2f} km/h steer={steering_deg:.2f} deg'
            )


def main(args=None):
    rclpy.init(args=args)
    node = CmdVelToAckermannNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()