#!/bin/bash
set -e

echo "=== Activating Nav2 stack ==="
sleep 5

for node in /map_server /planner_server /controller_server /behavior_server /bt_navigator /smoother_server
do
  echo "Configuring $node"
  ros2 lifecycle set $node configure
  sleep 1
done

for node in /map_server /planner_server /controller_server /behavior_server /bt_navigator /smoother_server
do
  echo "Activating $node"
  ros2 lifecycle set $node activate
  sleep 1
done

echo "=== Done activating Nav2 stack ==="
