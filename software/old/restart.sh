#!/usr/bin/env bash
set -e

echo "Restarting mosquitto..."
sudo systemctl restart mosquitto.service

echo "Restarting uwb-mqtt..."
sudo systemctl restart uwb-mqtt.service

echo "Restarting web-visu..."
sudo systemctl restart web-visu.service

echo "Restarting camera-stream..."
sudo systemctl restart camera-stream.service

echo "Restarting mpu-mqtt..."
sudo systemctl restart mpu-mqtt.service

echo "Restarting base-frame-mqtt..."
sudo systemctl restart base-frame-mqtt.service

echo
echo "Current status:"
sudo systemctl --no-pager --full status \
    mosquitto.service \
    uwb-mqtt.service \
    web-visu.service \
    camera-stream.service \
    mpu-mqtt.service \
    base-frame-mqtt.service || true