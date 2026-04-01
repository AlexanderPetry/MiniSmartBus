#!/usr/bin/env bash
set -e

APP_NAME="web-visu"
INSTALL_DIR="/opt/${APP_NAME}"
SERVICE_FILE="/etc/systemd/system/${APP_NAME}.service"
CURRENT_USER="${SUDO_USER:-$USER}"

echo "Installing ${APP_NAME}..."

sudo apt update
sudo apt install -y python3 python3-venv python3-pip mosquitto mosquitto-clients

sudo systemctl enable mosquitto
sudo systemctl start mosquitto

sudo mkdir -p "${INSTALL_DIR}"
sudo cp -r . "${INSTALL_DIR}"
sudo chown -R "${CURRENT_USER}:${CURRENT_USER}" "${INSTALL_DIR}"

cd "${INSTALL_DIR}"
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
WorkingDirectory=${INSTALL_DIR}
ExecStart=${INSTALL_DIR}/.venv/bin/python ${INSTALL_DIR}/RaspberryPi/webVisu.py
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