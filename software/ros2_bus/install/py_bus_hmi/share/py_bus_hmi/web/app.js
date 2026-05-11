const speedSlider = document.getElementById('speed-slider');
const steeringSlider = document.getElementById('steering-slider');
const speedValue = document.getElementById('speed-value');
const steeringValue = document.getElementById('steering-value');
const commandState = document.getElementById('command-state');

let sendTimer = null;

function updateSliderLabels() {
  speedValue.textContent = Number(speedSlider.value).toFixed(2) + ' km/h';
  steeringValue.textContent = Number(steeringSlider.value).toFixed(1) + ' deg';
}

async function sendDriverCommand() {
  const payload = {
    speed_kmh: Number(speedSlider.value),
    steering_deg: Number(steeringSlider.value),
  };

  try {
    const response = await fetch('/api/driver_command', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload),
    });

    const result = await response.json();

    if (result.ok) {
      commandState.textContent =
        `sent speed=${result.sent.speed_kmh.toFixed(2)} km/h, ` +
        `steering=${result.sent.steering_deg.toFixed(1)} deg`;
    } else {
      commandState.textContent = 'failed to send command';
    }
  } catch (error) {
    commandState.textContent = 'failed to send command';
  }
}

function scheduleDriverCommand() {
  updateSliderLabels();

  if (sendTimer) {
    clearTimeout(sendTimer);
  }

  sendTimer = setTimeout(sendDriverCommand, 120);
}

async function updateData() {
  try {
    const response = await fetch('/api/data');
    const data = await response.json();

    document.getElementById('imu').textContent =
      JSON.stringify(data.imu, null, 2);

    document.getElementById('uwb').textContent =
      JSON.stringify(data.uwb, null, 2);

    document.getElementById('driver').textContent =
      JSON.stringify(data.driver, null, 2);

    document.getElementById('last-command').textContent =
      JSON.stringify(data.last_command, null, 2);
  } catch (error) {
    document.getElementById('imu').textContent = 'failed to load imu data';
    document.getElementById('uwb').textContent = 'failed to load uwb data';
    document.getElementById('driver').textContent = 'failed to load driver data';
    document.getElementById('last-command').textContent = 'failed to load last command';
  }
}

speedSlider.addEventListener('input', scheduleDriverCommand);
steeringSlider.addEventListener('input', scheduleDriverCommand);

setInterval(updateData, 500);
updateSliderLabels();
updateData();
