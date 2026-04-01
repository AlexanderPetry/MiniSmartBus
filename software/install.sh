#!/usr/bin/env bash
set -e

APP_NAME="web-visu"
CURRENT_USER="${SUDO_USER:-$USER}"
BASE_DIR="/home/${CURRENT_USER}"
LIVE_DIR="${BASE_DIR}/MiniSmartBus-live"
SERVICE_FILE="/etc/systemd/system/${APP_NAME}.service"

echo "Installing ${APP_NAME} into stable git directory..."
echo "User: ${CURRENT_USER}"
echo "Live directory: ${LIVE_DIR}"

sudo apt update
sudo apt install -y python3 python3-venv python3-pip git mosquitto mosquitto-clients

sudo systemctl enable mosquitto
sudo systemctl start mosquitto

mkdir -p "${LIVE_DIR}"

if [ ! -d "${LIVE_DIR}/.git" ]; then
    echo "Initializing stable git checkout in ${LIVE_DIR}..."
    git clone https://github.com/AlexanderPetry/MiniSmartBus.git "${LIVE_DIR}"
else
    echo "Stable git checkout already exists, pulling latest changes..."
    git -C "${LIVE_DIR}" pull
fi

cd "${LIVE_DIR}"

python3 -m venv .venv
. .venv/bin/activate
pip install --upgrade pip
pip install flask paho-mqtt

sudo tee "${SERVICE_FILE}" > /dev/null <<EOF
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

sudo systemctl daemon-reload
sudo systemctl enable "${APP_NAME}.service"
sudo systemctl restart "${APP_NAME}.service"

echo "Install complete."
echo "Service status:"
sudo systemctl status "${APP_NAME}.service" --no-pager