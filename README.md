# UCL Robotics & AI 23fall Year 1 Final Project: Adaptive Fin Ray Inspired Tree Climbing Robot

## Overview
This project involves the development of an adaptive fin ray inspired tree climbing robot. The robot is designed to climb trees using a combination of mechanical, electronic, and software components. This README provides a comprehensive guide on how to assemble, program, and operate the robot.

## Table of Contents
- [Mechanical Assembly](#mechanical-assembly)
- [Electronics Setup](#electronics-setup)
- [Programming Guide](#programming-guide)
- [Algorithm Explanation](#algorithm-explanation)
- [Reflection and Improvements](#reflection-and-improvements)

## Mechanical Assembly
To assemble the robot, follow these steps:
1. **Attach the Grippers:**
   - Secure the grippers to the designated slots on the robot frame using screws and nuts.
   - Ensure that the grippers are firmly attached and can move without obstruction.

2. **Install the Flippers:**
   - Mount the flippers to the frame, ensuring they are aligned properly for optimal flipping motion.
   - Use the provided brackets and screws to secure the flippers in place.

3. **Attach the Rotating Mechanism:**
   - Fix the rotating mechanism at the base of the robot.
   - Ensure that the rotation axis is free of any obstructions and can rotate smoothly.

## Electronics Setup
To set up the electronics, follow these steps:
1. **Connect the Servos:**
   - Attach the servo motors to the grippers, flippers, and rotating mechanism.
   - Connect the servo motor wires to the appropriate pins on the Arduino board as specified in the code comments.

2. **Wire the Ultrasonic Sensors:**
   - Connect the ultrasonic sensors to the designated pins on the Arduino for obstacle detection.
   - Ensure the trigger and echo pins are correctly connected.

3. **Connect the Force Sensitive Resistors (FSRs):**
   - Attach the FSRs to the grippers to measure the gripping force.
   - Connect the FSRs to the analog input pins on the Arduino.

## Programming Guide
To program the robot, follow these steps:
1. **Clone the repository:**
   ```sh
   git clone https://github.com/william-Dic/Adaptive-Fin-Ray-Inspired-Tree-Climbing-Robot-UCL-RAI-24fall-.git

2. **Open the project in your preferred Arduino IDE:**

   - Navigate to the cloned repository directory and open the .ino file in the Arduino IDE.

3. **Connect the robot's hardware components:**

   - Follow the wiring instructions in the code comments to connect all hardware components to the Arduino board.

4. **Upload the code to the Arduino board:**

   - Connect the Arduino board to your computer via USB.
   
   - Select the appropriate board and port in the Arduino IDE, then upload the code.

5. **Monitor the serial output:**

   - Open the Serial Monitor in the Arduino IDE to view debugging and operational status messages.
