#!/usr/bin/env bash
set -e

APP_NAME="web-visu"
INSTALL_DIR="/opt/${APP_NAME}"
SERVICE_FILE="/etc/systemd/system/${APP_NAME}.service"

echo "Uninstalling ${APP_NAME}..."

if systemctl list-unit-files | grep -q "^${APP_NAME}.service"; then
    sudo systemctl stop "${APP_NAME}.service" || true
    sudo systemctl disable "${APP_NAME}.service" || true
fi

sudo rm -f "${SERVICE_FILE}"
sudo systemctl daemon-reload

sudo rm -rf "${INSTALL_DIR}"

echo "Uninstall complete."
echo "Note: Mosquitto was left installed."