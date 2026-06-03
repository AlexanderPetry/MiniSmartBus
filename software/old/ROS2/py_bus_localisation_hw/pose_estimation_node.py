import math

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Quaternion, TransformStamped
from nav_msgs.msg import Odometry
from tf2_ros import TransformBroadcaster

from py_bus_interfaces.msg import ImuData, UwbData


def yaw_to_quat(yaw: float) -> Quaternion:
    q = Quaternion()
    q.x = 0.0
    q.y = 0.0
    q.z = math.sin(yaw * 0.5)
    q.w = math.cos(yaw * 0.5)
    return q


def wrap(a: float) -> float:
    return (a + math.pi) % (2.0 * math.pi) - math.pi


class PoseEstimator(Node):
    def __init__(self):
        super().__init__('pose_estimator')

        self.sub_imu = self.create_subscription(ImuData, 'imu_data', self.imu_cb, 50)
        self.sub_uwb = self.create_subscription(UwbData, 'uwb_data', self.uwb_cb, 20)
        self.pub = self.create_publisher(Odometry, '/odometry/filtered', 10)
        self.tf = TransformBroadcaster(self)

        self.x = None
        self.y = None
        self.yaw = 0.0

        self.last_imu_t = None
        self.last_uwb = None

        self.vyaw = 0.0
        self.gyro_bias = 0.0
        self.bias_n = 0
        self.bias_samples = 200

        self.last_publish_t = None
        self.filtered_vx_world = 0.0
        self.filtered_vy_world = 0.0

        self.uwb_position_alpha = 0.15
        self.velocity_alpha = 0.2

        self.uwb_min_motion_for_velocity = 0.08
        self.uwb_jump_reject = 1.5

        self.publish_timer = self.create_timer(0.05, self.timer_publish)

        self.get_logger().info('Pose estimator started')

    def imu_cb(self, msg: ImuData):
        t = self.get_clock().now().nanoseconds * 1e-9
        gz = math.radians(float(msg.gyro_z))

        if self.last_imu_t is None:
            self.last_imu_t = t
            return

        dt = t - self.last_imu_t
        self.last_imu_t = t

        if dt <= 0.0 or dt > 0.2:
            return

        if self.bias_n < self.bias_samples:
            self.gyro_bias = (self.gyro_bias * self.bias_n + gz) / (self.bias_n + 1)
            self.bias_n += 1
            self.vyaw = 0.0
            return

        self.vyaw = gz - self.gyro_bias

        if abs(self.vyaw) < math.radians(0.5):
            self.vyaw = 0.0

        self.yaw = wrap(self.yaw + self.vyaw * dt)

    def uwb_cb(self, msg: UwbData):
        t = self.get_clock().now().nanoseconds * 1e-9
        x_meas = float(msg.x)
        y_meas = float(msg.y)

        if self.x is None or self.y is None or self.last_uwb is None:
            self.x = x_meas
            self.y = y_meas
            self.last_uwb = (x_meas, y_meas, t)
            return

        last_x_meas, last_y_meas, last_t = self.last_uwb
        dt = t - last_t
        if dt <= 0.0:
            return

        dx_meas = x_meas - last_x_meas
        dy_meas = y_meas - last_y_meas
        dist_meas = math.hypot(dx_meas, dy_meas)

        if dist_meas > self.uwb_jump_reject:
            self.get_logger().warning(
                f'Rejecting UWB jump: {dist_meas:.2f} m'
            )
            return

        self.x = (1.0 - self.uwb_position_alpha) * self.x + self.uwb_position_alpha * x_meas
        self.y = (1.0 - self.uwb_position_alpha) * self.y + self.uwb_position_alpha * y_meas

        vx_world_meas = 0.0
        vy_world_meas = 0.0

        if dist_meas >= self.uwb_min_motion_for_velocity and dt > 1e-3:
            vx_world_meas = dx_meas / dt
            vy_world_meas = dy_meas / dt

        self.filtered_vx_world = (
            (1.0 - self.velocity_alpha) * self.filtered_vx_world
            + self.velocity_alpha * vx_world_meas
        )
        self.filtered_vy_world = (
            (1.0 - self.velocity_alpha) * self.filtered_vy_world
            + self.velocity_alpha * vy_world_meas
        )

        self.last_uwb = (x_meas, y_meas, t)

    def timer_publish(self):
        t = self.get_clock().now().nanoseconds * 1e-9
        self.publish(t)

    def publish(self, t: float):
        if self.x is None or self.y is None:
            return

        cy = math.cos(self.yaw)
        sy = math.sin(self.yaw)

        vx_body = cy * self.filtered_vx_world + sy * self.filtered_vy_world
        vy_body = -sy * self.filtered_vx_world + cy * self.filtered_vy_world

        if abs(vx_body) < 0.02:
            vx_body = 0.0
        if abs(vy_body) < 0.02:
            vy_body = 0.0
        if abs(self.vyaw) < math.radians(0.5):
            self.vyaw = 0.0

        odom = Odometry()
        odom.header.stamp = self.get_clock().now().to_msg()
        odom.header.frame_id = 'odom'
        odom.child_frame_id = 'base_link'

        odom.pose.pose.position.x = self.x
        odom.pose.pose.position.y = self.y
        odom.pose.pose.position.z = 0.0
        odom.pose.pose.orientation = yaw_to_quat(self.yaw)

        odom.twist.twist.linear.x = vx_body
        odom.twist.twist.linear.y = vy_body
        odom.twist.twist.linear.z = 0.0
        odom.twist.twist.angular.x = 0.0
        odom.twist.twist.angular.y = 0.0
        odom.twist.twist.angular.z = self.vyaw

        pose_cov = [0.0] * 36
        pose_cov[0] = 0.25
        pose_cov[7] = 0.25
        pose_cov[14] = 9999.0
        pose_cov[21] = 9999.0
        pose_cov[28] = 9999.0
        pose_cov[35] = 0.20

        twist_cov = [0.0] * 36
        twist_cov[0] = 0.10
        twist_cov[7] = 0.10
        twist_cov[14] = 9999.0
        twist_cov[21] = 9999.0
        twist_cov[28] = 9999.0
        twist_cov[35] = 0.10

        odom.pose.covariance = pose_cov
        odom.twist.covariance = twist_cov

        self.pub.publish(odom)

        tf = TransformStamped()
        tf.header.stamp = odom.header.stamp
        tf.header.frame_id = 'odom'
        tf.child_frame_id = 'base_link'
        tf.transform.translation.x = self.x
        tf.transform.translation.y = self.y
        tf.transform.translation.z = 0.0
        tf.transform.rotation = odom.pose.pose.orientation
        self.tf.sendTransform(tf)


def main():
    rclpy.init()
    node = PoseEstimator()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()