#!/usr/bin/env bash
set -e

WEB_APP_NAME="web-visu"
SERIAL_APP_NAME="uwb-mqtt"
CAMERA_APP_NAME="camera-stream"
MPU_APP_NAME="mpu-mqtt"
RC_CAR_APP_NAME="base-frame-mqtt"

CURRENT_USER="${SUDO_USER:-$USER}"
BASE_DIR="/home/${CURRENT_USER}"
LIVE_DIR="${BASE_DIR}/MiniSmartBus-live"

WEB_SERVICE_FILE="/etc/systemd/system/${WEB_APP_NAME}.service"
SERIAL_SERVICE_FILE="/etc/systemd/system/${SERIAL_APP_NAME}.service"
CAMERA_SERVICE_FILE="/etc/systemd/system/${CAMERA_APP_NAME}.service"
MPU_SERVICE_FILE="/etc/systemd/system/${MPU_APP_NAME}.service"
RC_CAR_SERVICE_FILE="/etc/systemd/system/${RC_CAR_APP_NAME}.service"

echo "Uninstalling services..."

sudo systemctl stop "${WEB_APP_NAME}.service" || true
sudo systemctl disable "${WEB_APP_NAME}.service" || true

sudo systemctl stop "${SERIAL_APP_NAME}.service" || true
sudo systemctl disable "${SERIAL_APP_NAME}.service" || true

sudo systemctl stop "${CAMERA_APP_NAME}.service" || true
sudo systemctl disable "${CAMERA_APP_NAME}.service" || true

sudo systemctl stop "${MPU_APP_NAME}.service" || true
sudo systemctl disable "${MPU_APP_NAME}.service" || true

sudo systemctl stop "${RC_CAR_APP_NAME}.service" || true
sudo systemctl disable "${RC_CAR_APP_NAME}.service" || true

sudo rm -f "${WEB_SERVICE_FILE}"
sudo rm -f "${SERIAL_SERVICE_FILE}"
sudo rm -f "${CAMERA_SERVICE_FILE}"
sudo rm -f "${MPU_SERVICE_FILE}"
sudo rm -f "${RC_CAR_SERVICE_FILE}"

sudo systemctl daemon-reload
sudo systemctl reset-failed || true

rm -rf "${LIVE_DIR}"

echo "Uninstall complete."
echo "Mosquitto, I2C packages, and Picamera2 were left installed."
echo "User group membership was not reverted."