#!/usr/bin/env bash
set -e

WEB_APP_NAME="web-visu"
SERIAL_APP_NAME="uwb-mqtt"
CAMERA_APP_NAME="camera-stream"
MPU_APP_NAME="mpu-mqtt"

CURRENT_USER="${SUDO_USER:-$USER}"
BASE_DIR="/home/${CURRENT_USER}"
LIVE_DIR="${BASE_DIR}/MiniSmartBus-live"
MODEL_DIR="${LIVE_DIR}/software/RaspberryPi/models"
YOLO_MODEL_FILE="${MODEL_DIR}/yolov8n.pt"
YOLO_MODEL_URL="https://github.com/ultralytics/assets/releases/download/v8.3.0/yolov8n.pt"

WEB_SERVICE_FILE="/etc/systemd/system/${WEB_APP_NAME}.service"
SERIAL_SERVICE_FILE="/etc/systemd/system/${SERIAL_APP_NAME}.service"
CAMERA_SERVICE_FILE="/etc/systemd/system/${CAMERA_APP_NAME}.service"
MPU_SERVICE_FILE="/etc/systemd/system/${MPU_APP_NAME}.service"

REPO_URL="https://github.com/AlexanderPetry/MiniSmartBus.git"

echo "Installing services into stable git directory..."
echo "User: ${CURRENT_USER}"
echo "Live directory: ${LIVE_DIR}"

sudo apt update
sudo apt install -y \
    python3 \
    python3-venv \
    python3-pip \
    python3-picamera2 \
    python3-smbus \
    i2c-tools \
    git \
    wget \
    mosquitto \
    mosquitto-clients

if command -v raspi-config >/dev/null 2>&1; then
    sudo raspi-config nonint do_i2c 0 || true
fi

echo "i2c-dev" | sudo tee /etc/modules-load.d/i2c.conf >/dev/null
sudo modprobe i2c-dev || true

sudo systemctl enable mosquitto
sudo systemctl start mosquitto

sudo usermod -a -G dialout "${CURRENT_USER}" || true
sudo usermod -a -G video "${CURRENT_USER}" || true
sudo usermod -a -G i2c "${CURRENT_USER}" || true

mkdir -p "${LIVE_DIR}"

if [ ! -d "${LIVE_DIR}/.git" ]; then
    echo "Cloning repository into ${LIVE_DIR}..."
    git clone "${REPO_URL}" "${LIVE_DIR}"
else
    echo "Repository already exists, pulling latest changes..."
    git -C "${LIVE_DIR}" pull
fi

cd "${LIVE_DIR}"

rm -rf .venv
python3 -m venv --system-site-packages .venv
. .venv/bin/activate
pip install --upgrade pip
pip install flask paho-mqtt pyserial requests ultralytics opencv-python

mkdir -p "${MODEL_DIR}"

if [ -f "${YOLO_MODEL_FILE}" ]; then
    echo "YOLO model already exists: ${YOLO_MODEL_FILE}"
else
    echo "Downloading YOLO model to ${YOLO_MODEL_FILE} ..."
    wget -O "${YOLO_MODEL_FILE}" "${YOLO_MODEL_URL}"
fi

sudo tee "${WEB_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=Position Web MQTT Service
After=network.target mosquitto.service
Wants=mosquitto.service

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${LIVE_DIR}/software/RaspberryPi
ExecStart=${LIVE_DIR}/.venv/bin/python ${LIVE_DIR}/software/RaspberryPi/webVisu.py
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

sudo tee "${SERIAL_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=UWB Serial to MQTT Service
After=network.target mosquitto.service
Wants=mosquitto.service

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${LIVE_DIR}/software/RaspberryPi
ExecStart=${LIVE_DIR}/.venv/bin/python ${LIVE_DIR}/software/RaspberryPi/DMW1001_PositionExtracter.py
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

sudo tee "${CAMERA_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=CSI Camera Stream Service
After=network.target
Wants=network.target

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${LIVE_DIR}/software/RaspberryPi
ExecStart=${LIVE_DIR}/.venv/bin/python ${LIVE_DIR}/software/RaspberryPi/vision.py
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

sudo tee "${MPU_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=MPU6050 I2C to MQTT Service
After=network.target mosquitto.service
Wants=mosquitto.service

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${LIVE_DIR}/software/RaspberryPi
ExecStart=${LIVE_DIR}/.venv/bin/python ${LIVE_DIR}/software/RaspberryPi/mpu.py
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload

sudo systemctl enable "${WEB_APP_NAME}.service"
sudo systemctl enable "${SERIAL_APP_NAME}.service"
sudo systemctl enable "${CAMERA_APP_NAME}.service"
sudo systemctl enable "${MPU_APP_NAME}.service"

sudo systemctl restart "${WEB_APP_NAME}.service"
sudo systemctl restart "${SERIAL_APP_NAME}.service"
sudo systemctl restart "${CAMERA_APP_NAME}.service"
sudo systemctl restart "${MPU_APP_NAME}.service"

echo
echo "Install complete."
echo
echo "MPU MQTT service status:"
sudo systemctl status "${MPU_APP_NAME}.service" --no-pager || true
echo
echo "Test the topic with:"
echo "mosquitto_sub -t minismartbus/sensors/mpu6050"
echo
echo "Note: because dialout/video/i2c group membership changed, a logout/login or reboot may be needed before serial, camera, and I2C sensor access works."