#!/usr/bin/env python3
import json
import time
import socket
from datetime import datetime, timezone

import smbus
import paho.mqtt.client as mqtt

MQTT_BROKER = "127.0.0.1"
MQTT_PORT = 1883
MQTT_TOPIC = "minismartbus/sensors/mpu6050"

I2C_BUS = 1
MPU_ADDR = 0x68

PWR_MGMT_1   = 0x6B
ACCEL_XOUT_H = 0x3B
TEMP_OUT_H   = 0x41
GYRO_XOUT_H  = 0x43

PUBLISH_INTERVAL = 0.5

bus = smbus.SMBus(I2C_BUS)

def read_word_2c(reg):
    high = bus.read_byte_data(MPU_ADDR, reg)
    low = bus.read_byte_data(MPU_ADDR, reg + 1)
    value = (high << 8) | low
    if value >= 0x8000:
        value = -((65535 - value) + 1)
    return value

def init_mpu():
    bus.write_byte_data(MPU_ADDR, PWR_MGMT_1, 0)
    time.sleep(0.1)

def read_sample():
    accel_x = read_word_2c(ACCEL_XOUT_H)
    accel_y = read_word_2c(ACCEL_XOUT_H + 2)
    accel_z = read_word_2c(ACCEL_XOUT_H + 4)

    temp_raw = read_word_2c(TEMP_OUT_H)

    gyro_x = read_word_2c(GYRO_XOUT_H)
    gyro_y = read_word_2c(GYRO_XOUT_H + 2)
    gyro_z = read_word_2c(GYRO_XOUT_H + 4)

    return {
        "timestamp": datetime.now(timezone.utc).isoformat(),
        "host": socket.gethostname(),
        "sensor": "SEN0142_MPU6050",
        "i2c_bus": I2C_BUS,
        "i2c_address": hex(MPU_ADDR),
        "accel_g": {
            "x": accel_x / 16384.0,
            "y": accel_y / 16384.0,
            "z": accel_z / 16384.0,
        },
        "gyro_dps": {
            "x": gyro_x / 131.0,
            "y": gyro_y / 131.0,
            "z": gyro_z / 131.0,
        },
        "temperature_c": (temp_raw / 340.0) + 36.53,
        "raw": {
            "accel_x": accel_x,
            "accel_y": accel_y,
            "accel_z": accel_z,
            "gyro_x": gyro_x,
            "gyro_y": gyro_y,
            "gyro_z": gyro_z,
            "temp": temp_raw,
        },
    }

def main():
    client = mqtt.Client()
    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()

    init_mpu()

    while True:
        payload = read_sample()
        client.publish(MQTT_TOPIC, json.dumps(payload), qos=0, retain=False)
        time.sleep(PUBLISH_INTERVAL)

if __name__ == "__main__":
    main()