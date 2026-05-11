import re
import threading
import time
import serial
from serial import SerialException

import rclpy
from rclpy.node import Node
from rclpy.executors import ExternalShutdownException

from py_bus_interfaces.msg import DriverCommand, DriverStatus


class DriverNode(Node):
    SERIAL_PORT = "/dev/serial/by-id/usb-Silicon_Labs_CP2102_USB_to_UART_Bridge_Controller_0001-if00-port0"
    BAUD_RATE = 115200
    SERIAL_TIMEOUT = 0.2
    SERIAL_WRITE_TIMEOUT = 0.5
    STATUS_PUBLISH_PERIOD = 0.2
    RECONNECT_PERIOD = 1.0
    INITIAL_CONNECT_DELAY = 2.0

    DISCONNECT_LOG_PERIOD = 2.0
    DUPLICATE_EPS_SPEED = 0.01
    DUPLICATE_EPS_STEER = 0.01

    def __init__(self):
        super().__init__('driver_node')

        self.publisher_ = self.create_publisher(DriverStatus, 'esp32_status', 10)
        self.subscription = self.create_subscription(
            DriverCommand,
            'esp32_cmd',
            self.command_callback,
            10
        )

        self.serial_lock = threading.Lock()
        self.status_lock = threading.Lock()
        self.running = True
        self.ser = None

        self.last_commanded_speed_kmh = 0.0
        self.last_commanded_steering_deg = 0.0
        self.latest_status = self.make_default_status()

        self.last_sent_speed_kmh = None
        self.last_sent_steering_deg = None
        self.last_disconnect_log_time = 0.0
        self.last_connect_fail_log_time = 0.0
        self.connected_once = False

        self.reader_thread = threading.Thread(
            target=self.serial_reader_loop,
            daemon=True
        )
        self.reader_thread.start()

        self.timer = self.create_timer(
            self.STATUS_PUBLISH_PERIOD,
            self.timer_callback
        )

        self.get_logger().info(
            f'ESP32 driver node started. Target port: {self.SERIAL_PORT}'
        )

    def make_default_status(self):
        msg = DriverStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.source = 'DISCONNECTED'
        msg.rc_steering_us = 0
        msg.rc_throttle_us = 0
        msg.commanded_speed_kmh = 0.0
        msg.commanded_steering_deg = 0.0
        msg.applied_speed_kmh = 0.0
        msg.applied_steering_deg = 0.0
        msg.batt_voltage = 0.0
        msg.batt_pct = 0.0
        msg.raw_line = 'waiting for esp32 data...'
        return msg

    def now_sec(self):
        return time.monotonic()

    def should_log_disconnect(self):
        now = self.now_sec()
        if now - self.last_disconnect_log_time >= self.DISCONNECT_LOG_PERIOD:
            self.last_disconnect_log_time = now
            return True
        return False

    def same_command(self, speed_a, steer_a, speed_b, steer_b):
        if speed_b is None or steer_b is None:
            return False
        return (
            abs(speed_a - speed_b) < self.DUPLICATE_EPS_SPEED and
            abs(steer_a - steer_b) < self.DUPLICATE_EPS_STEER
        )

    def connect_serial(self):
        try:
            ser = serial.Serial(
                port=self.SERIAL_PORT,
                baudrate=self.BAUD_RATE,
                timeout=self.SERIAL_TIMEOUT,
                write_timeout=self.SERIAL_WRITE_TIMEOUT
            )

            time.sleep(self.INITIAL_CONNECT_DELAY)
            ser.reset_input_buffer()
            ser.reset_output_buffer()

            with self.serial_lock:
                self.ser = ser

            self.connected_once = True
            self.get_logger().info(
                f'Connected to ESP32 on {self.SERIAL_PORT} @ {self.BAUD_RATE} baud'
            )
            return True

        except Exception as e:
            now = self.now_sec()
            if now - self.last_connect_fail_log_time >= self.DISCONNECT_LOG_PERIOD:
                self.last_connect_fail_log_time = now
                self.get_logger().warning(f'Could not open serial port: {e}')
            return False

    def disconnect_serial(self):
        with self.serial_lock:
            ser = self.ser
            self.ser = None

        if ser is not None:
            try:
                if ser.is_open:
                    ser.close()
            except Exception:
                pass

    def command_callback(self, msg):
        speed = max(-4.0, min(4.0, float(msg.speed_kmh)))
        steering = max(-35.0, min(35.0, float(msg.steering_deg)))

        self.last_commanded_speed_kmh = speed
        self.last_commanded_steering_deg = steering

        if self.same_command(
            speed, steering,
            self.last_sent_speed_kmh, self.last_sent_steering_deg
        ):
            return

        serial_cmd = f'[speed={speed:.2f}, steering={steering:.2f}]\n'

        try:
            with self.serial_lock:
                if self.ser is None or not self.ser.is_open:
                    if self.should_log_disconnect():
                        self.get_logger().warning(
                            'Serial not connected, skipping command send'
                        )
                    return

                self.ser.write(serial_cmd.encode('ascii'))
                self.ser.flush()

            self.last_sent_speed_kmh = speed
            self.last_sent_steering_deg = steering

        except Exception as e:
            if self.should_log_disconnect():
                self.get_logger().warning(f'Failed to send serial command: {e}')
            self.disconnect_serial()

    def is_plausible_status_line(self, line: str) -> bool:
        if not line:
            return False
        printable = sum(1 for c in line if 32 <= ord(c) <= 126)
        if printable < max(8, int(len(line) * 0.8)):
            return False
        return ('SRC=' in line) or line.startswith('OK:') or line.startswith('ERR:')

    def serial_reader_loop(self):
        while self.running:
            try:
                if self.ser is None:
                    if not self.connect_serial():
                        time.sleep(self.RECONNECT_PERIOD)
                        continue

                with self.serial_lock:
                    if self.ser is None or not self.ser.is_open:
                        raise SerialException('serial port not open')
                    raw = self.ser.readline()

                if not raw:
                    continue

                line = raw.decode('ascii', errors='ignore').strip()
                if not line:
                    continue

                if not self.is_plausible_status_line(line):
                    continue

                parsed_msg = self.parse_status_line(line)

                with self.status_lock:
                    self.latest_status = parsed_msg

            except Exception as e:
                if self.should_log_disconnect():
                    self.get_logger().warning(f'Serial read error: {e}')
                self.disconnect_serial()
                time.sleep(self.RECONNECT_PERIOD)

    def parse_status_line(self, line):
        msg = DriverStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.source = 'UNKNOWN'
        msg.rc_steering_us = 0
        msg.rc_throttle_us = 0
        msg.commanded_speed_kmh = self.last_commanded_speed_kmh
        msg.commanded_steering_deg = self.last_commanded_steering_deg
        msg.applied_speed_kmh = self.last_commanded_speed_kmh
        msg.applied_steering_deg = self.last_commanded_steering_deg
        msg.batt_voltage = 0.0
        msg.batt_pct = 0.0
        msg.raw_line = line

        src_match = re.search(r'SRC=([A-Z_]+)', line)
        if src_match:
            msg.source = src_match.group(1)

        rc1_match = re.search(r'rc1=(\d+)us', line)
        if rc1_match:
            msg.rc_steering_us = int(rc1_match.group(1))

        rc2_match = re.search(r'rc2=(\d+)us', line)
        if rc2_match:
            msg.rc_throttle_us = int(rc2_match.group(1))

        serial_speed_match = re.search(r'serialSpeed=([-\d.]+)\s*km/h', line)
        if serial_speed_match:
            msg.commanded_speed_kmh = float(serial_speed_match.group(1))

        serial_steer_match = re.search(r'serialSteer=([-\d.]+)\s*deg', line)
        if serial_steer_match:
            msg.commanded_steering_deg = float(serial_steer_match.group(1))

        batt_match = re.search(r'batt=([-\d.]+)V\s*\(([-\d.]+)%\)', line)
        if batt_match:
            msg.batt_voltage = float(batt_match.group(1))
            msg.batt_pct = float(batt_match.group(2))

        applied_speed_match = re.search(r'(?<!serial)speed=([-\d.]+)\s*km/h', line)
        if applied_speed_match:
            msg.applied_speed_kmh = float(applied_speed_match.group(1))

        applied_steer_match = re.search(r'(?<!serial)steer=([-\d.]+)\s*deg', line)
        if applied_steer_match:
            msg.applied_steering_deg = float(applied_steer_match.group(1))

        if msg.source == 'SERIAL':
            msg.applied_speed_kmh = msg.commanded_speed_kmh
            msg.applied_steering_deg = msg.commanded_steering_deg

        return msg

    def timer_callback(self):
        with self.status_lock:
            msg = self.latest_status
            msg.stamp = self.get_clock().now().to_msg()

            if self.ser is None:
                msg.source = 'DISCONNECTED'
                msg.commanded_speed_kmh = self.last_commanded_speed_kmh
                msg.commanded_steering_deg = self.last_commanded_steering_deg
                msg.applied_speed_kmh = 0.0
                msg.applied_steering_deg = 0.0
                msg.raw_line = 'serial disconnected'

            self.publisher_.publish(msg)

    def close_serial(self):
        self.running = False

        try:
            if self.reader_thread.is_alive():
                self.reader_thread.join(timeout=1.0)
        except Exception:
            pass

        self.disconnect_serial()


def main(args=None):
    driver_node = None

    try:
        rclpy.init(args=args)
        driver_node = DriverNode()
        rclpy.spin(driver_node)

    except (KeyboardInterrupt, ExternalShutdownException):
        pass

    finally:
        try:
            if driver_node is not None:
                driver_node.close_serial()
                driver_node.destroy_node()
        except Exception:
            pass

        rclpy.shutdown()


if __name__ == '__main__':
    main()
