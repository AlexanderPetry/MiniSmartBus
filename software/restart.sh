#!/usr/bin/env bash
set -e

echo "Restarting web-visu.service..."
sudo systemctl restart web-visu.service

echo "Restarting mosquitto service..."
sudo systemctl restart mosquitto.service