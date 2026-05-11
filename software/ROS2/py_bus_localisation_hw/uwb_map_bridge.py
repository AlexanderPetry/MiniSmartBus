import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped
from tf2_ros import TransformBroadcaster
from py_bus_interfaces.msg import UwbData
from nav_msgs.msg import Odometry

class UwbMapBridge(Node):
    def __init__(self):
        super().__init__('uwb_map_bridge')
        self.tf_broadcaster = TransformBroadcaster(self)
        self.sub_uwb = self.create_subscription(UwbData, 'uwb_data', self.uwb_cb, 10)
        self.current_odom_pos = (0.0, 0.0)
        self.create_subscription(Odometry, '/odometry/filtered', self.odom_cb, 10)

    def odom_cb(self, msg):
        self.current_odom_pos = (msg.pose.pose.position.x, msg.pose.pose.position.y)

    def uwb_cb(self, msg):
        # Calculate the drift offset
        offset_x = msg.x - self.current_odom_pos[0]
        offset_y = msg.y - self.current_odom_pos[1]

        # Publish map -> odom transform
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = 'map'
        t.child_frame_id = 'odom'
        t.transform.translation.x = offset_x
        t.transform.translation.y = offset_y
        t.transform.rotation.w = 1.0 # No rotation change
        self.tf_broadcaster.sendTransform(t)

def main():
    rclpy.init(); rclpy.spin(UwbMapBridge()); rclpy.shutdown()