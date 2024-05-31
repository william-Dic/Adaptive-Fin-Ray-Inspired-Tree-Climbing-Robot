# UCL Robotics & AI 23/24 Year 1 Final Project: Adaptive Fin Ray Inspired Tree Climbing Robot

## Overview
This project involves the development of an adaptive fin ray inspired tree climbing robot. The robot is designed to climb trees using a combination of mechanical, electronic, and software components. This README provides a comprehensive guide on how to assemble, program, and operate the robot.
![Robot Image](images/robot_image_1.jpg)
![Robot Image](images/robot_image_2.jpg)

## Table of Contents
- [Mechanical Assembly](#mechanical-assembly)
- [Electronics Setup](#electronics-setup)
- [Programming Guide](#programming-guide)

## Mechanical Assembly
To assemble the robot, follow these steps:
1. **Attach the Grippers:**
   - Secure the TPU Fin Ray grippers at the designated slots on the PLA gripper holders using strong adhesives such as hot glue.
   - Ensure that the gripper holders are firmly attached to the servo motor housing with nuts and bolts, allowing the quarter 14-teeth gears to move without obstruction.

2. **Install the Flipper:**
   - Mount the rack linkage to the flipper spine with nuts and bolts.
   - Check for alignment to ensure proper flipping motion.

4. **Attach the Rotating Mechanism:**
   - Attach the 24-teeth pinion gear in alignment with the mini servo motor housing using a threaded rod and nuts.
   - Ensure flushed contact between rack and pinion to allow smooth rotation along the rack linkage.

## Electronics Setup
To set up the electronics, follow these steps:
1. **Connect the Servos:**
   - Attach the servo motors to the grippers, flipper, and rotating mechanism.
   - Connect the servo motor wires to the appropriate pins on the Arduino board as specified in the code comments.

2. **Wire the Ultrasonic Sensors:**
   - Connect the ultrasonic sensors to the designated pins on the Arduino for obstacle and ceiling detection.
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
