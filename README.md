# RobotArm

![RobotArm](https://github.com/matthewjpicone/RobotArm/blob/main/RobotArm.jpg)

This repository contains a simple robotic arm project designed for educational purposes. The arm design is derived from the Braccio project by [Basso Delmoro Gramaglia](https://www.hackster.io/basso-delmoro-gramaglia/bracc-ino-robotic-arm-e015e3). 

## Project Overview

This is the first arm the author has built, and they were interested in the mechanics of such a project. The arm is controlled by an Arduino Nano and responds to a joystick and a light sensor that has a laser diode opposite. The electronics for this project are fairly straightforward, and a schematic is provided below.

## Video Demo

Here's a video demo of the arm in action:

[![Watch the video](https://img.youtube.com/vi/70W0WIBirDQ/hqdefault.jpg)](https://youtu.be/70W0WIBirDQ)

## Circuit Schematic

The circuit schematic for this project is shown below:

![Robot Arm Schematic](https://github.com/matthewjpicone/RobotArm/blob/main/Robot%20Arm%20V2.1_schem.png?raw=true)

A single Arduino Nano drives 7 servos, receives inputs from 2 limit switches on the gripper, a laser receiver, and a 6-axis joystick. There is 1 pin dedicated to the LEDs and 1 dedicated to the laser. Everything is powered by a 5V 5A power supply with a 10v capacitor soldered over the pins. There is also an OLED display available for showing current servo values.

## Code Overview

The code for this project starts with the pin assignments and some variables to take care of the array positions for each part of the arm. The `servoParams` follows this pattern:

**PIN | INT TARGET | INT CURRENT | INT LOWER LIMIT DEGREES | INT UPPER LIMIT DEGREES**

The code then declares some variables to store the inputs and begins defining the functions.

The `moveServo` function takes in 6 arguments, each one is used to set the new target position for each servo. These values are then written to the array, and then the function blocks the program until the arm reaches the desired position. This choice was made to allow the arm to complete a move before accepting new commands to avoid any issues with collisions, etc.

The `joystickRead` function handles user input, and each axis is mapped twice and can be selected by pushing the button. This allows full control over the arm on a single stick. There is an offset built in to handle the play associated with the lower-end joysticks as it does produce irregular values when idle. Once the joystick has been read, the `moveServo` function is called.

The `flashLED` function takes in milliseconds the time to keep the LED on (freq) and the time it should be off (freq2), then utilizes a timer to flash them accordingly without blocking the rest of the program.

The `serialEvent` function handles commands that will be sent via the future python script.

The `setup` handles the pin modes and joystick offsets. During boot, it is important not to touch the joystick so that the appropriate offset can be written. The loop then runs the `joystickRead` and `flashLED` functions. A small, simple program was written for the arm to move golf balls around the circuit.
