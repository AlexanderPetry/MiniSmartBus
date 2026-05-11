const navState = document.getElementById('nav-state');
const canvas = document.getElementById('map-canvas');
const ctx = canvas.getContext('2d');

const modeManualBtn = document.getElementById('mode-manual');
const modeAutoBtn = document.getElementById('mode-auto');
const modeLabel = document.getElementById('mode-label');

const toolGoalBtn = document.getElementById('tool-goal');
const toolObstacleBtn = document.getElementById('tool-obstacle');
const clearObstaclesBtn = document.getElementById('clear-obstacles');
const toggleObstaclesBtn = document.getElementById('toggle-obstacles');
const toolLabel = document.getElementById('tool-label');

const cmdvelLabel = document.getElementById('cmdvel-label');
const obstacleLabel = document.getElementById('obstacle-label');
const hintLabel = document.getElementById('hint-label');

const ros = new ROSLIB.Ros({
  url: 'ws://' + window.location.hostname + ':9090'
});

let mapInfo = null;
let mapGrid = null;
let currentPose = null;
let pendingGoalPosition = null;
let goalPose = null;

let globalPlan = null;
let smoothedPlan = null;
let localPlan = null;

let driveMode = 'manual';
let activeTool = 'goal';

let latestCmdVel = null;

let showObstacles = true;
let obstacles = [];
let obstacleDraft = null;
let draggingObstacleId = null;
let dragOffset = { x: 0, y: 0 };

ros.on('connection', () => {
  navState.textContent = 'connected to rosbridge';
  refreshDriveMode();
});

ros.on('error', (error) => {
  navState.textContent = 'rosbridge connection failed';
  console.error('rosbridge error:', error);
});

ros.on('close', () => {
  navState.textContent = 'rosbridge connection closed';
});

const mapTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/map',
  messageType: 'nav_msgs/OccupancyGrid'
});

const odomTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/odometry/filtered',
  messageType: 'nav_msgs/Odometry'
});

const goalTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/goal_pose',
  messageType: 'geometry_msgs/PoseStamped'
});

const globalPlanTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/plan',
  messageType: 'nav_msgs/Path'
});

const smoothedPlanTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/plan_smoothed',
  messageType: 'nav_msgs/Path'
});

const localPlanTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/local_plan',
  messageType: 'nav_msgs/Path'
});

const cmdVelTopic = new ROSLIB.Topic({
  ros: ros,
  name: '/cmd_vel',
  messageType: 'geometry_msgs/Twist'
});

mapTopic.subscribe((msg) => {
  mapInfo = msg.info;
  mapGrid = msg.data;
  resizeCanvasToMap();
  redraw();
});

odomTopic.subscribe((msg) => {
  currentPose = msg.pose.pose;
  redraw();
});

globalPlanTopic.subscribe((msg) => {
  globalPlan = msg;
  redraw();
});

smoothedPlanTopic.subscribe((msg) => {
  smoothedPlan = msg;
  redraw();
});

localPlanTopic.subscribe((msg) => {
  localPlan = msg;
  redraw();
});

cmdVelTopic.subscribe((msg) => {
  latestCmdVel = msg;
  updateCmdVelUi();
});

async function refreshDriveMode() {
  try {
    const response = await fetch('/api/data');
    const data = await response.json();
    driveMode = (data.drive_mode || 'manual').toLowerCase();
    updateModeUi();
  } catch (error) {
    console.error('Failed to fetch drive mode:', error);
  }
}

async function setDriveMode(mode) {
  try {
    const response = await fetch('/api/drive_mode', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ mode })
    });

    const data = await response.json();

    if (!response.ok || !data.ok) {
      navState.textContent = data.error || 'failed to set drive mode';
      return;
    }

    driveMode = data.mode;
    updateModeUi();
    navState.textContent = `drive mode set to ${driveMode}`;
  } catch (error) {
    console.error('Failed to set drive mode:', error);
    navState.textContent = 'failed to set drive mode';
  }
}

async function publishObstaclesToRos() {
  try {
    const response = await fetch('/api/obstacles', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        obstacles: obstacles.map((o) => ({
          id: o.id,
          x1: Math.round(o.x1),
          y1: Math.round(o.y1),
          x2: Math.round(o.x2),
          y2: Math.round(o.y2)
        }))
      })
    });

    const data = await response.json();

    if (!response.ok || !data.ok) {
      navState.textContent = data.error || 'failed to publish test obstacles';
      return;
    }

    navState.textContent = `published ${data.count} test obstacles to ${data.topic}`;
  } catch (error) {
    console.error('Failed to publish obstacles:', error);
    navState.textContent = 'failed to publish test obstacles';
  }
}

async function clearObstaclesInRos() {
  try {
    const response = await fetch('/api/obstacles', {
      method: 'DELETE'
    });

    const data = await response.json();

    if (!response.ok || !data.ok) {
      navState.textContent = data.error || 'failed to clear test obstacles';
      return;
    }

    navState.textContent = `cleared test obstacles on ${data.topic}`;
  } catch (error) {
    console.error('Failed to clear obstacles in ROS:', error);
    navState.textContent = 'failed to clear test obstacles';
  }
}

function updateModeUi() {
  modeLabel.textContent = `mode: ${driveMode}`;
  modeManualBtn.disabled = driveMode === 'manual';
  modeAutoBtn.disabled = driveMode === 'auto';
}

function updateToolUi() {
  toolLabel.textContent = `tool: ${activeTool}`;
  toolGoalBtn.classList.toggle('active', activeTool === 'goal');
  toolObstacleBtn.classList.toggle('active', activeTool === 'obstacle');

  if (activeTool === 'goal') {
    hintLabel.textContent = 'goal tool: click once for position, click again for heading';
    canvas.style.cursor = 'crosshair';
  } else {
    hintLabel.textContent = 'obstacle tool: click-drag to create, drag inside shape to move, right click shape to delete';
    canvas.style.cursor = 'copy';
  }
}

function updateCmdVelUi() {
  if (!latestCmdVel) {
    cmdvelLabel.textContent = 'waiting for /cmd_vel...';
    return;
  }

  const lx = Number(latestCmdVel.linear?.x || 0);
  const az = Number(latestCmdVel.angular?.z || 0);
  cmdvelLabel.textContent = `linear.x=${lx.toFixed(2)} m/s | angular.z=${az.toFixed(2)} rad/s`;
}

function updateObstacleUi() {
  obstacleLabel.textContent = `${obstacles.length} obstacle${obstacles.length === 1 ? '' : 's'}${showObstacles ? '' : ' (hidden)'}`;
  toggleObstaclesBtn.textContent = showObstacles ? 'Hide obstacles' : 'Show obstacles';
}

modeManualBtn.addEventListener('click', () => {
  setDriveMode('manual');
});

modeAutoBtn.addEventListener('click', () => {
  setDriveMode('auto');
});

toolGoalBtn.addEventListener('click', () => {
  activeTool = 'goal';
  obstacleDraft = null;
  draggingObstacleId = null;
  updateToolUi();
  redraw();
});

toolObstacleBtn.addEventListener('click', () => {
  activeTool = 'obstacle';
  pendingGoalPosition = null;
  updateToolUi();
  redraw();
});

clearObstaclesBtn.addEventListener('click', async () => {
  obstacles = [];
  obstacleDraft = null;
  draggingObstacleId = null;
  updateObstacleUi();
  redraw();
  await clearObstaclesInRos();
  navState.textContent = 'all browser-side obstacles cleared';
});

toggleObstaclesBtn.addEventListener('click', () => {
  showObstacles = !showObstacles;
  updateObstacleUi();
  redraw();
});

function resizeCanvasToMap() {
  if (!mapInfo) return;
  canvas.width = mapInfo.width;
  canvas.height = mapInfo.height;
}

function worldToCanvas(x, y) {
  if (!mapInfo) return { x: 0, y: 0 };
  const px = (x - mapInfo.origin.position.x) / mapInfo.resolution;
  const py = canvas.height - ((y - mapInfo.origin.position.y) / mapInfo.resolution);
  return { x: px, y: py };
}

function canvasToWorld(px, py) {
  if (!mapInfo) return { x: 0, y: 0 };
  const x = mapInfo.origin.position.x + px * mapInfo.resolution;
  const y = mapInfo.origin.position.y + (canvas.height - py) * mapInfo.resolution;
  return { x, y };
}

function yawToQuaternion(yaw) {
  return {
    x: 0.0,
    y: 0.0,
    z: Math.sin(yaw / 2.0),
    w: Math.cos(yaw / 2.0)
  };
}

function quaternionToYaw(q) {
  return Math.atan2(
    2.0 * (q.w * q.z + q.x * q.y),
    1.0 - 2.0 * (q.y * q.y + q.z * q.z)
  );
}

function drawMap() {
  if (!mapInfo || !mapGrid) {
    ctx.fillStyle = '#e0e0e0';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    return;
  }

  const image = ctx.createImageData(mapInfo.width, mapInfo.height);

  for (let y = 0; y < mapInfo.height; y++) {
    for (let x = 0; x < mapInfo.width; x++) {
      const mapIndex = x + (mapInfo.height - 1 - y) * mapInfo.width;
      const pixelIndex = (y * mapInfo.width + x) * 4;
      let value = mapGrid[mapIndex];

      if (showObstacles && pointInsideAnyObstacle(x, y)) {
        value = 100;
      }

      let color = 255;
      if (value === -1) {
        color = 205;
      } else {
        color = 255 - Math.round((value / 100.0) * 255);
      }

      image.data[pixelIndex + 0] = color;
      image.data[pixelIndex + 1] = color;
      image.data[pixelIndex + 2] = color;
      image.data[pixelIndex + 3] = 255;
    }
  }

  ctx.putImageData(image, 0, 0);
}

function pointInsideRect(px, py, rect) {
  const left = Math.min(rect.x1, rect.x2);
  const right = Math.max(rect.x1, rect.x2);
  const top = Math.min(rect.y1, rect.y2);
  const bottom = Math.max(rect.y1, rect.y2);
  return px >= left && px <= right && py >= top && py <= bottom;
}

function pointInsideAnyObstacle(px, py) {
  return obstacles.some((obs) => pointInsideRect(px, py, obs));
}

function findObstacleAt(px, py) {
  for (let i = obstacles.length - 1; i >= 0; i--) {
    if (pointInsideRect(px, py, obstacles[i])) {
      return obstacles[i];
    }
  }
  return null;
}

function normalizeRect(rect) {
  return {
    id: rect.id,
    x1: Math.min(rect.x1, rect.x2),
    y1: Math.min(rect.y1, rect.y2),
    x2: Math.max(rect.x1, rect.x2),
    y2: Math.max(rect.y1, rect.y2)
  };
}

function drawObstacle(rect, fillStyle, strokeStyle, dashed = false) {
  const r = normalizeRect(rect);
  const w = Math.max(1, r.x2 - r.x1);
  const h = Math.max(1, r.y2 - r.y1);

  ctx.save();
  ctx.fillStyle = fillStyle;
  ctx.strokeStyle = strokeStyle;
  ctx.lineWidth = 2;
  if (dashed) ctx.setLineDash([6, 4]);
  ctx.fillRect(r.x1, r.y1, w, h);
  ctx.strokeRect(r.x1, r.y1, w, h);
  ctx.restore();
}

function drawObstacles() {
  if (!showObstacles) return;

  obstacles.forEach((obs) => {
    drawObstacle(obs, 'rgba(220, 38, 38, 0.30)', 'rgba(185, 28, 28, 0.95)');
  });

  if (obstacleDraft) {
    drawObstacle(obstacleDraft, 'rgba(234, 179, 8, 0.25)', 'rgba(202, 138, 4, 1)', true);
  }
}

function drawPath(pathMsg, color, lineWidth, dash = []) {
  if (!pathMsg || !pathMsg.poses || pathMsg.poses.length === 0) return;

  ctx.save();
  ctx.strokeStyle = color;
  ctx.lineWidth = lineWidth;
  ctx.setLineDash(dash);
  ctx.lineJoin = 'round';
  ctx.lineCap = 'round';
  ctx.beginPath();

  pathMsg.poses.forEach((poseStamped, index) => {
    const p = worldToCanvas(
      poseStamped.pose.position.x,
      poseStamped.pose.position.y
    );

    if (index === 0) {
      ctx.moveTo(p.x, p.y);
    } else {
      ctx.lineTo(p.x, p.y);
    }
  });

  ctx.stroke();
  ctx.restore();
}

function drawRobot() {
  if (!currentPose) return;

  const p = worldToCanvas(currentPose.position.x, currentPose.position.y);
  const yaw = quaternionToYaw(currentPose.orientation);

  ctx.fillStyle = '#18a558';
  ctx.beginPath();
  ctx.arc(p.x, p.y, 6, 0, Math.PI * 2);
  ctx.fill();

  const arrowLen = 18;
  ctx.strokeStyle = '#18a558';
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.moveTo(p.x, p.y);
  ctx.lineTo(p.x + arrowLen * Math.cos(yaw), p.y - arrowLen * Math.sin(yaw));
  ctx.stroke();
}

function drawGoal() {
  if (!goalPose) return;

  const p = worldToCanvas(goalPose.position.x, goalPose.position.y);
  const yaw = quaternionToYaw(goalPose.orientation);

  ctx.fillStyle = '#d62828';
  ctx.beginPath();
  ctx.arc(p.x, p.y, 6, 0, Math.PI * 2);
  ctx.fill();

  const arrowLen = 18;
  ctx.strokeStyle = '#d62828';
  ctx.lineWidth = 2;
  ctx.beginPath();
  ctx.moveTo(p.x, p.y);
  ctx.lineTo(p.x + arrowLen * Math.cos(yaw), p.y - arrowLen * Math.sin(yaw));
  ctx.stroke();
}

function drawPendingGoal() {
  if (!pendingGoalPosition) return;

  const p = worldToCanvas(pendingGoalPosition.x, pendingGoalPosition.y);
  ctx.fillStyle = '#ff9800';
  ctx.beginPath();
  ctx.arc(p.x, p.y, 5, 0, Math.PI * 2);
  ctx.fill();
}

function drawLegend() {
  const items = [
    { label: 'global plan', color: '#1976d2' },
    { label: 'smoothed plan', color: '#7b2cbf' },
    { label: 'local plan', color: '#ff9800' },
    { label: 'robot', color: '#18a558' },
    { label: 'goal', color: '#d62828' },
    { label: 'test obstacle', color: '#b91c1c' }
  ];

  const x = 12;
  const y = 12;
  const rowH = 18;
  const boxW = 170;
  const boxH = items.length * rowH + 12;

  ctx.save();
  ctx.fillStyle = 'rgba(255,255,255,0.92)';
  ctx.fillRect(x, y, boxW, boxH);
  ctx.strokeStyle = 'rgba(0,0,0,0.15)';
  ctx.strokeRect(x, y, boxW, boxH);

  items.forEach((item, i) => {
    const yy = y + 10 + i * rowH;

    ctx.strokeStyle = item.color;
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.moveTo(x + 10, yy + 6);
    ctx.lineTo(x + 30, yy + 6);
    ctx.stroke();

    ctx.fillStyle = '#111';
    ctx.font = '12px sans-serif';
    ctx.fillText(item.label, x + 38, yy + 10);
  });

  ctx.restore();
}

function redraw() {
  drawMap();
  drawObstacles();
  drawPath(globalPlan, '#1976d2', 3);
  drawPath(smoothedPlan, '#7b2cbf', 3, [8, 6]);
  drawPath(localPlan, '#ff9800', 2);
  drawRobot();
  drawGoal();
  drawPendingGoal();
  drawLegend();
}

function getCanvasPoint(event) {
  const rect = canvas.getBoundingClientRect();
  const scaleX = canvas.width / rect.width;
  const scaleY = canvas.height / rect.height;

  return {
    x: (event.clientX - rect.left) * scaleX,
    y: (event.clientY - rect.top) * scaleY
  };
}

canvas.addEventListener('mousedown', (event) => {
  if (!mapInfo) return;
  if (activeTool !== 'obstacle') return;

  const p = getCanvasPoint(event);
  const hit = findObstacleAt(p.x, p.y);

  if (hit) {
    draggingObstacleId = hit.id;
    dragOffset.x = p.x - hit.x1;
    dragOffset.y = p.y - hit.y1;
    return;
  }

  obstacleDraft = {
    id: Date.now() + Math.random(),
    x1: p.x,
    y1: p.y,
    x2: p.x,
    y2: p.y
  };
  redraw();
});

canvas.addEventListener('mousemove', (event) => {
  if (!mapInfo) return;
  if (activeTool !== 'obstacle') return;

  const p = getCanvasPoint(event);

  if (draggingObstacleId !== null) {
    const obs = obstacles.find((o) => o.id === draggingObstacleId);
    if (!obs) return;

    const width = obs.x2 - obs.x1;
    const height = obs.y2 - obs.y1;

    obs.x1 = p.x - dragOffset.x;
    obs.y1 = p.y - dragOffset.y;
    obs.x2 = obs.x1 + width;
    obs.y2 = obs.y1 + height;
    redraw();
    return;
  }

  if (obstacleDraft) {
    obstacleDraft.x2 = p.x;
    obstacleDraft.y2 = p.y;
    redraw();
  }
});

canvas.addEventListener('mouseup', async () => {
  if (activeTool !== 'obstacle') return;

  if (draggingObstacleId !== null) {
    draggingObstacleId = null;
    updateObstacleUi();
    redraw();
    await publishObstaclesToRos();
    return;
  }

  if (obstacleDraft) {
    const r = normalizeRect(obstacleDraft);
    const minSize = 4;
    if ((r.x2 - r.x1) >= minSize && (r.y2 - r.y1) >= minSize) {
      obstacles.push(r);
      navState.textContent = `obstacle added: ${obstacles.length} total`;
    }
    obstacleDraft = null;
    updateObstacleUi();
    await publishObstaclesToRos();
    redraw();
  }
});

canvas.addEventListener('mouseleave', () => {
  if (activeTool !== 'obstacle') return;
  draggingObstacleId = null;
});

canvas.addEventListener('contextmenu', async (event) => {
  if (activeTool !== 'obstacle') return;

  event.preventDefault();
  const p = getCanvasPoint(event);
  const hit = findObstacleAt(p.x, p.y);
  if (!hit) return;

  obstacles = obstacles.filter((o) => o.id !== hit.id);
  updateObstacleUi();
  redraw();
  await publishObstaclesToRos();
});

canvas.addEventListener('click', (event) => {
  if (activeTool !== 'goal') return;

  if (driveMode !== 'auto') {
    navState.textContent = 'switch to auto mode before sending a navigation goal';
    return;
  }

  if (!mapInfo) {
    navState.textContent = 'map not received yet';
    return;
  }

  const rect = canvas.getBoundingClientRect();
  const scaleX = canvas.width / rect.width;
  const scaleY = canvas.height / rect.height;

  const px = (event.clientX - rect.left) * scaleX;
  const py = (event.clientY - rect.top) * scaleY;
  const world = canvasToWorld(px, py);

  if (!pendingGoalPosition) {
    pendingGoalPosition = world;
    navState.textContent =
      `goal position set: x=${world.x.toFixed(2)}, y=${world.y.toFixed(2)} — click again to set heading`;
    redraw();
    return;
  }

  const dx = world.x - pendingGoalPosition.x;
  const dy = world.y - pendingGoalPosition.y;
  const yaw = Math.atan2(dy, dx);
  const orientation = yawToQuaternion(yaw);

  goalPose = {
    position: {
      x: pendingGoalPosition.x,
      y: pendingGoalPosition.y,
      z: 0.0
    },
    orientation: orientation
  };

  const msg = new ROSLIB.Message({
    header: {
      frame_id: 'map'
    },
    pose: goalPose
  });

  goalTopic.publish(msg);

  navState.textContent =
    `goal sent: x=${goalPose.position.x.toFixed(2)}, y=${goalPose.position.y.toFixed(2)}, yaw=${yaw.toFixed(2)} rad`;

  pendingGoalPosition = null;
  redraw();
});

updateModeUi();
updateToolUi();
updateCmdVelUi();
updateObstacleUi();
