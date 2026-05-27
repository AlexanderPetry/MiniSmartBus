# Miniature Autonomous Driving Bus Platform

A modular 1:20 scale autonomous bus test platform for experimenting with autonomous driving in a simplified indoor bus depot environment. The project was developed as a bachelor thesis at Lapland UAS and focuses on creating a practical, low-cost, and expandable platform for testing robotics and vehicle software without requiring full-scale infrastructure. 

## Overview

This project explores how a small-scale bus, indoor localization, and modular robotics software can be combined into a usable development platform for autonomous driving experiments. The current system provides a working prototype with separate mechanical, embedded, and high-level processing layers, making it suitable for testing, demonstrations, and future student development. 

The platform already supports manual radio driving, manual command driving through an interface, camera-based object detection, path planning, and position estimation. Fully stable autonomous driving is not yet achieved because pose estimation still needs improvement, but the main subsystems are already integrated and functional. 

## Project goals

The main goal of the project is to create a realistic and testable small-scale autonomous bus platform within a limited development period. The system is intended to make experimentation easier, cheaper, and more flexible than testing directly on full-scale autonomous vehicles.

A second goal is to keep the platform modular, so that future improvements can be made without redesigning the whole system. This applies to both hardware and software, including the localization stack, perception pipeline, navigation logic, and electronics. 

## System architecture

The platform is divided into three main layers: a mechanical frame, a base driving unit, and a brain processing unit. This separation makes the system easier to debug, extend, and maintain over time.

### 1. Mechanical frame
The mechanical frame provides the physical structure of the bus and supports the mounted electronics and sensors. It uses a four-wheel layout with Ackermann steering and is designed to resemble a small public transport bus while remaining practical for prototyping. 

### 2. Base driving unit
The base driving unit handles low-level vehicle control. It is built around an ESP32 and controls the steering servo, drive motors, radio receiver input, and communication with the Raspberry Pi. 

### 3. Brain processing unit
The brain unit runs on a Raspberry Pi 5 and is responsible for higher-level functions such as localization, navigation, perception, and interface logic. It uses ROS2 to organize the software into separate modules that can be expanded later. 

## Main features

- Manual radio driving for direct control and safety override. 
- Manual command driving through a software interface. 
- Camera-based object detection using YOLOv8. 
- Indoor position estimation using UWB and IMU data. 
- Path planning through a ROS2 and Nav2-based structure. 
- Modular hardware and software architecture for future development. 

## Technologies used

The project combines mechanical design, embedded systems, and robotics software into one platform. Key technologies and components mentioned in the thesis include Fusion 360, 3D printing, ESP32, Raspberry Pi 5, ROS2, UWB localization modules, IMU sensing, Raspberry Pi Camera 2, and YOLOv8-based perception. 

## Hardware summary

The drive system uses TT motors and an L298N motor driver, while steering is controlled by an SG90 servo. The platform uses an 11.1V battery, custom PCB-based power distribution, and separate processing/control responsibilities between the ESP32 and Raspberry Pi. 

For localization and perception, the system uses a DWM1001 UWB module, three UWB anchors, an IMU board, and a Raspberry Pi Camera 2. The Raspberry Pi 5 with 16 GB RAM runs Ubuntu 24.04 and ROS2 for high-level operation. 

## Software summary

The ESP32 software manages direct motor and steering control, radio input, and UART communication with the Raspberry Pi. On the Raspberry Pi side, the system is organized into ROS2 packages for hardware communication, localization, navigation, perception, interfaces, and startup support. 

The software stack includes custom packages for driver communication, localization hardware and logic, navigation integration, perception logic, and a web-based interface layer. Nav2 is used as the navigation framework, while ROS2 acts as the main communication and modularization backbone. 

## Current status

The platform is functional as a prototype and demonstrates that the overall architecture works. The strongest results are on the hardware side, where the mechanical structure, PCB, power distribution, and modular split between low-level and high-level control were successfully implemented. 

At the moment, autonomous driving is still limited by unstable pose estimation and software integration issues. Because of that, the project should currently be seen as a strong development base rather than a fully finished autonomous vehicle. 

## Why this project matters

Testing autonomous vehicle systems at full scale is expensive and difficult to adapt quickly. This project shows that a smaller and more accessible test platform can still provide meaningful value for prototyping, education, demonstrations, and future mobility research. 

The thesis also highlights the project’s relevance to innovation and sustainable transport research, especially as a reusable platform for Lapland UAS and future students. Its modular structure makes it useful not only as a prototype, but also as a long-term development foundation. 

## Future improvements

Possible next steps mentioned in the thesis include improving the localization and odometry pipeline, stabilizing autonomous driving, updating the PCB and wiring design, using more existing ROS2 tools where suitable, and adding extra sensors such as LiDAR. 

These improvements would make the platform easier to reuse, more reliable in demonstrations, and better suited for future autonomous driving experiments. 
## Repository structure

miniBus/<br>
├── README.md<br>
├── .gitignore<br>
│<br>
├── docs/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── overview.md<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── build_guide.md<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── wiring.md<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── communication_protocol.md<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── troubleshooting.md<br>
│<br>
├── hardware/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── 3D_design/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── BOM/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── notes/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── renders/<br>
│<br>
├── electronics/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── base_frame/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── pcb/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── schematic/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── layout/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── BOM/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── fab/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── wiring_schematic/     
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── firmware/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── notes/<br>
│   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── perception_stack/<br>
│<br>
└── software/       <br>          


## Acknowledgements
Developed as a bachelor thesis project at Lapland University of Applied Sciences. The platform was created as a reusable base for autonomous bus testing, demonstrations, and future student work. 
