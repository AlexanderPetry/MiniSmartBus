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
PI_DIR="${LIVE_DIR}/software/RaspberryPi"
MODEL_DIR="${LIVE_DIR}/software/RaspberryPi/models"
YOLO_MODEL_FILE="${MODEL_DIR}/yolov8n.pt"
YOLO_MODEL_URL="https://github.com/ultralytics/assets/releases/download/v8.3.0/yolov8n.pt"

WEB_SERVICE_FILE="/etc/systemd/system/${WEB_APP_NAME}.service"
SERIAL_SERVICE_FILE="/etc/systemd/system/${SERIAL_APP_NAME}.service"
CAMERA_SERVICE_FILE="/etc/systemd/system/${CAMERA_APP_NAME}.service"
MPU_SERVICE_FILE="/etc/systemd/system/${MPU_APP_NAME}.service"
RC_CAR_SERVICE_FILE="/etc/systemd/system/${RC_CAR_APP_NAME}.service"

REPO_URL="https://github.com/AlexanderPetry/MiniSmartBus.git"

RC_CAR_SCRIPT_SRC="${PI_DIR}/rc_car_serial_mqtt.py"
RC_CAR_DEFAULT_SERIAL="/dev/ttyACM0"
RC_CAR_MQTT_TOPIC="minismartbus/rc_car/state"


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
mkdir -p "${PI_DIR}"

if [ -f "${YOLO_MODEL_FILE}" ]; then
    echo "YOLO model already exists: ${YOLO_MODEL_FILE}"
else
    echo "Downloading YOLO model to ${YOLO_MODEL_FILE} ..."
    wget -O "${YOLO_MODEL_FILE}" "${YOLO_MODEL_URL}"
fi

if [ -f "./software/RaspberryPi/rc_car_serial_mqtt.py" ]; then
    chmod +x "./software/RaspberryPi/rc_car_serial_mqtt.py"
else
    echo "WARNING: ./software/RaspberryPi/rc_car_serial_mqtt.py not found in repo yet."
    echo "Copy the provided rc_car_serial_mqtt.py into ${PI_DIR}/ before starting the service."
fi

sudo tee "${WEB_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=Position Web MQTT Service
After=network.target mosquitto.service
Wants=mosquitto.service

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${PI_DIR}
ExecStart=${LIVE_DIR}/.venv/bin/python ${PI_DIR}/webVisu.py
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
WorkingDirectory=${PI_DIR}
ExecStart=${LIVE_DIR}/.venv/bin/python ${PI_DIR}/DMW1001_PositionExtracter.py
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
WorkingDirectory=${PI_DIR}
ExecStart=${LIVE_DIR}/.venv/bin/python ${PI_DIR}/vision.py
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
WorkingDirectory=${PI_DIR}
ExecStart=${LIVE_DIR}/.venv/bin/python ${PI_DIR}/mpu.py
Restart=always
RestartSec=2

[Install]
WantedBy=multi-user.target
EOF

sudo tee "${RC_CAR_SERVICE_FILE}" > /dev/null <<EOF
[Unit]
Description=RC Car Serial to MQTT Service
After=network.target mosquitto.service
Wants=mosquitto.service

[Service]
Type=simple
User=${CURRENT_USER}
WorkingDirectory=${PI_DIR}
Environment=MQTT_BROKER=localhost
Environment=MQTT_PORT=1883
Environment=SERIAL_PORT=${RC_CAR_DEFAULT_SERIAL}
Environment=SERIAL_BAUD=115200
Environment=SERIAL_AUTO_DISCOVER=1
Environment=MQTT_BASE_TOPIC=minismartbus/rc_car
Environment=MQTT_JSON_TOPIC=${RC_CAR_MQTT_TOPIC}
ExecStart=${LIVE_DIR}/.venv/bin/python ${PI_DIR}/baseFrame.py
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
sudo systemctl enable "${RC_CAR_APP_NAME}.service"

sudo systemctl restart "${WEB_APP_NAME}.service"
sudo systemctl restart "${SERIAL_APP_NAME}.service"
sudo systemctl restart "${CAMERA_APP_NAME}.service"
sudo systemctl restart "${MPU_APP_NAME}.service"
sudo systemctl restart "${RC_CAR_APP_NAME}.service"

echo
echo "Install complete."
echo
echo "RC car MQTT service status:"
sudo systemctl status "${RC_CAR_APP_NAME}.service" --no-pager || true
echo
echo "Test the RC car topic with:"
echo "mosquitto_sub -t ${RC_CAR_MQTT_TOPIC}"
echo
echo "Raw per-line topic mirror example:"
echo "mosquitto_sub -t 'minismartbus/rc_car/raw/#'"
echo
echo "Note: because dialout/video/i2c group membership changed, a logout/login or reboot may be needed before serial, camera, and I2C sensor access works."