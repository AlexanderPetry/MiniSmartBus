import time
import smbus
import rclpy
from rclpy.node import Node
from rclpy.executors import ExternalShutdownException

from py_bus_interfaces.msg import ImuData




class ImuNode(Node):
    I2C_BUS = 1
    MPU_ADDR = 0x68

    PWR_MGMT_1   = 0x6B
    ACCEL_XOUT_H = 0x3B
    TEMP_OUT_H   = 0x41
    GYRO_XOUT_H  = 0x43


    def __init__(self):
        super().__init__('imu_node')
        self.publisher_ = self.create_publisher(ImuData, 'imu_data', 10)

        self.bus = smbus.SMBus(self.I2C_BUS)
        self.init_mpu()

        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0
        
    def init_mpu(self):
        self.bus.write_byte_data(self.MPU_ADDR, self.PWR_MGMT_1, 0)
        time.sleep(0.1)        

    def read_word_2c(self, reg):
        high = self.bus.read_byte_data(self.MPU_ADDR, reg)
        low = self.bus.read_byte_data(self.MPU_ADDR, reg + 1)
        value = (high << 8) | low
        if value >= 0x8000:
            value = -((65535 - value) + 1)
        return value

    def read_sample(self):
        msg = ImuData()

        msg.accel_x = self.read_word_2c(self.ACCEL_XOUT_H) / 16384.0
        msg.accel_y = self.read_word_2c(self.ACCEL_XOUT_H + 2) / 16384.0
        msg.accel_z = self.read_word_2c(self.ACCEL_XOUT_H + 4) / 16384.0

        msg.temp = (self.read_word_2c(self.TEMP_OUT_H) / 340.0) + 36.53

        msg.gyro_x = self.read_word_2c(self.GYRO_XOUT_H) / 131.0
        msg.gyro_y = self.read_word_2c(self.GYRO_XOUT_H + 2) / 131.0
        msg.gyro_z = self.read_word_2c(self.GYRO_XOUT_H + 4) / 131.0

        msg.sample_id = self.i

        return msg

    def timer_callback(self):
        msg = self.read_sample()
        self.publisher_.publish(msg)
        self.get_logger().info(
            f'Publishing IMU sample {msg.sample_id}: '
            f'accel=({msg.accel_x:.2f}, {msg.accel_y:.2f}, {msg.accel_z:.2f}) '
            f'gyro=({msg.gyro_x:.2f}, {msg.gyro_y:.2f}, {msg.gyro_z:.2f}) '
            f'temp={msg.temp:.2f}'
        )
        self.i += 1




def main(args=None):
    try:
        rclpy.init(args=args)
        imu_node = ImuNode()
        rclpy.spin(imu_node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        try:
            imu_node.destroy_node()
        except:
            pass
        rclpy.shutdown()


if __name__ == '__main__':
    main()