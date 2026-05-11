import math
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Quaternion, TransformStamped
from nav_msgs.msg import Odometry
from tf2_ros import TransformBroadcaster
from py_bus_interfaces.msg import ImuData, UwbData


def yaw_to_quat(yaw):
    q = Quaternion()
    q.z = math.sin(yaw * 0.5)
    q.w = math.cos(yaw * 0.5)
    return q


def wrap(a):
    return (a + math.pi) % (2.0 * math.pi) - math.pi


class PoseEstimator(Node):
    def __init__(self):
        super().__init__('pose_estimator')
        self.sub_imu = self.create_subscription(ImuData, 'imu_data', self.imu_cb, 10)
        self.sub_uwb = self.create_subscription(UwbData, 'uwb_data', self.uwb_cb, 10)
        self.pub = self.create_publisher(Odometry, '/odometry/filtered', 10)
        self.tf = TransformBroadcaster(self)

        self.x = None
        self.y = None
        self.yaw = 0.0
        self.last_uwb = None
        self.last_imu_t = None
        self.vyaw = 0.0
        self.gyro_bias = 0.0
        self.bias_n = 0

    def imu_cb(self, msg):
        t = self.get_clock().now().nanoseconds * 1e-9
        gz = math.radians(msg.gyro_z)

        if self.last_imu_t is not None:
            dt = t - self.last_imu_t
            if self.bias_n < 50:
                self.gyro_bias = (self.gyro_bias * self.bias_n + gz) / (self.bias_n + 1)
                self.bias_n += 1
            else:
                self.yaw = wrap(self.yaw + (gz - self.gyro_bias) * dt)
                self.vyaw = gz - self.gyro_bias

        self.last_imu_t = t

    def uwb_cb(self, msg):
        t = self.get_clock().now().nanoseconds * 1e-9
        x = float(msg.x)
        y = float(msg.y)

        if self.last_uwb is None:
            self.x, self.y = x, y
            self.last_uwb = (x, y, t)
            self.publish(t)
            return

        lx, ly, lt = self.last_uwb
        dt = max(t - lt, 1e-6)
        dx = x - lx
        dy = y - ly
        dist = math.hypot(dx, dy)

        if dist > 0.02:
            motion_yaw = math.atan2(dy, dx)
            self.yaw = wrap(0.7 * self.yaw + 0.3 * motion_yaw)
            vx = dx / dt
            vy = dy / dt
        else:
            vx = 0.0
            vy = 0.0

        self.x = 0.7 * self.x + 0.3 * x
        self.y = 0.7 * self.y + 0.3 * y
        self.last_uwb = (x, y, t)
        self.publish(t, vx, vy)

    def publish(self, t, vx=0.0, vy=0.0):
        odom = Odometry()
        odom.header.stamp = self.get_clock().now().to_msg()
        odom.header.frame_id = 'odom'
        odom.child_frame_id = 'base_link'
        odom.pose.pose.position.x = self.x if self.x is not None else 0.0
        odom.pose.pose.position.y = self.y if self.y is not None else 0.0
        odom.pose.pose.orientation = yaw_to_quat(self.yaw)
        odom.twist.twist.linear.x = vx
        odom.twist.twist.linear.y = vy
        odom.twist.twist.angular.z = self.vyaw
        self.pub.publish(odom)

        tf = TransformStamped()
        tf.header.stamp = odom.header.stamp
        tf.header.frame_id = 'odom'
        tf.child_frame_id = 'base_link'
        tf.transform.translation.x = odom.pose.pose.position.x
        tf.transform.translation.y = odom.pose.pose.position.y
        tf.transform.rotation = odom.pose.pose.orientation
        self.tf.sendTransform(tf)


def main():
    rclpy.init()
    node = PoseEstimator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
