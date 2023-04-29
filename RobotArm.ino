/*
Educational Robot Arm

Microcontroller: Arduino Nano

Author: Matthew PICONE
Date: 08/JAN/2023

Description: Small robot arm that responds to commands from a 6 axis joystick and serial.
*/

// Pin Assignments - ANALOG
#define JOYSTICK_Z A0
#define JOYSTICK_BUTTON A1
#define JOYSTICK_X A2
#define JOYSTICK_Y A3
#define SDA A4
#define SCL A5
#define BALL_DETECTOR A6
// #define unassigned A7  // Wire available in joystick loom

// Pin Assignments - DIGITAL
#define SERVO_BASE 2
#define SERVO_L1 3
#define SERVO_L2 4
#define SERVO_L3 5
#define SERVO_L4 6
#define SERVO_GRIPPER_1 7  // Terminal block on gripper.
#define SERVO_GRIPPER_2 8  // Terminal block on gripper.
#define LASER_EMITTER 9    // OUTPUT
#define LED 10
#define LIMIT_SWITCH_1 11  // INPUT_PULLUP
#define LIMIT_SWITCH_2 12  // INPUT_PULLUP
// #define UNASSIGNED 13 // NOT CONNECTED

// SERVO SETTINGS
#include <Servo.h>
const int servoCount = 7;

// Array positional references
int PIN = 0;
int TARGET_POS = 1;
int CURRENT_POS = 2;
int LOWER_LIMIT = 3;
int UPPER_LIMIT = 4;

// PIN | INT TARGET | INT CURRENT | INT LOWER LIMIT DEGREES | INT UPPER LIMIT DEGREES
int servoParams[servoCount][5] = {
  { SERVO_BASE, 90, 90, 40, 145 },
  { SERVO_L1, 25, 25, 25, 140 },
  { SERVO_L2, 20, 20, 20, 140 },
  { SERVO_L3, 130, 130, 0, 180 },
  { SERVO_L4, 50, 50, 0, 180 },
  { SERVO_GRIPPER_1, 180, 180, 110, 175 },
  { SERVO_GRIPPER_2, 180, 180, 110, 175 },
};

Servo servo[servoCount];  // Create Servo instances

// INPUT VARIABLES
int JOYSTICK_Z_OFFSET;
int JOYSTICK_X_OFFSET;
int JOYSTICK_Y_OFFSET;

int JOYSTICK_Z_VAL;
bool JOYSTICK_BUTTON_VAL;
int JOYSTICK_X_VAL;
int JOYSTICK_Y_VAL;
int BALL_DETECTOR_VAL;
bool LASER_EMITTER_VAL;
bool LED_VAL;
bool LIMIT_SWITCH_1_VAL;
bool LIMIT_SWITCH_2_VAL;

void moveServo(int s0, int s1, int s2, int s3, int s4, int s5, int s6) {
  // Writes target position to array then blocks program to move the arm to target position.
  // TODO - Add in check for gripper limit switches when theyre attached to auto stop on close 
  // - 15/01 Limit switches moved to centre of grips

  int newTarget[] = { s0, s1, s2, s3, s4, s5, s6 };
  for (int i = 0; i < servoCount; i++) {
    servoParams[i][TARGET_POS] = newTarget[i];
  }
  String targetStr = "Target: ";
  for (int print = 0; print < servoCount; print++) {
    targetStr += String(servoParams[print][TARGET_POS]) + ", ";
  }
  Serial.println(targetStr);
  int check = 0;
  while (check < servoCount) {

    for (int i = 0; i < servoCount; i++) {

      if (servoParams[i][CURRENT_POS] < servoParams[i][TARGET_POS]) {
        servoParams[i][CURRENT_POS]++;
      }
      if (servoParams[i][CURRENT_POS] > servoParams[i][TARGET_POS]) {
        servoParams[i][CURRENT_POS]--;
      }
      //Add in protection for wire loom (no servo stops)
      if (servoParams[i][TARGET_POS] > servoParams[i][UPPER_LIMIT]) {
        servoParams[i][TARGET_POS] = servoParams[i][UPPER_LIMIT];
      }
      if (servoParams[i][TARGET_POS] < servoParams[i][LOWER_LIMIT]) {
        servoParams[i][TARGET_POS] = servoParams[i][LOWER_LIMIT];
      }
      if (servoParams[i][TARGET_POS] == servoParams[i][CURRENT_POS]) {
        check++;
      } else {
        check = 0;
      }
      servo[i].write(servoParams[i][CURRENT_POS]);
      delay(2);
    }
  }
}

void joystickRead() {
  // Read joystick value and write to target array.
  int halfwayAnalog = 512;  // Halfway in normal range
  int scale = 5;            // Steps above / below
  int z = analogRead(JOYSTICK_Z);
  int y = analogRead(JOYSTICK_Y);
  int x = analogRead(JOYSTICK_X);

  // If statements added 10/01/23 to accomodate cheap three axis joystick with large ammount of play in joint.
  if (z - JOYSTICK_Z_OFFSET > 125 || JOYSTICK_Z_OFFSET - z > 125) {
    JOYSTICK_Z_VAL = map(z, JOYSTICK_Z_OFFSET - halfwayAnalog, JOYSTICK_Z_OFFSET + halfwayAnalog, -scale, scale);
  } else {
    JOYSTICK_Z_VAL = 0;
  }
  if (x - JOYSTICK_X_OFFSET > 100 || JOYSTICK_X_OFFSET - x > 100) {
    JOYSTICK_X_VAL = map(x, JOYSTICK_X_OFFSET - halfwayAnalog, JOYSTICK_X_OFFSET + halfwayAnalog, scale, -scale);
  } else {
    JOYSTICK_X_VAL = 0;
  }
  if (y - JOYSTICK_Y_OFFSET > 125 || JOYSTICK_Y_OFFSET - y > 125) {
    JOYSTICK_Y_VAL = map(y, JOYSTICK_Y_OFFSET - halfwayAnalog, JOYSTICK_Y_OFFSET + halfwayAnalog, scale, -scale);
  } else {
    JOYSTICK_Y_VAL = 0;
  }

// Check if is theres any user input then check for button input
if (JOYSTICK_Z_VAL !=0 || JOYSTICK_Y_VAL != 0 || JOYSTICK_X_VAL != 0){
  if (analogRead(JOYSTICK_BUTTON) < 512) {
    moveServo(servoParams[0][1], servoParams[1][1], servoParams[2][1], servoParams[3][1] + JOYSTICK_Y_VAL,
              servoParams[4][1] + JOYSTICK_X_VAL, servoParams[5][1] + JOYSTICK_Z_VAL, servoParams[6][1]);
  } else {
    moveServo(servoParams[0][1] + JOYSTICK_Z_VAL, servoParams[1][1] + JOYSTICK_X_VAL, 
    servoParams[2][1] + JOYSTICK_Y_VAL, servoParams[3][1], servoParams[4][1], servoParams[5][1], servoParams[6][1]);
}
}
}

int flashState = 0;
int currentMillis;
int LEDPrevious1 = 0;
int LEDPrevious2 = 0;
int LEDPrevious3 = 0;
int LEDPrevious4 = 0;
void flashLED(int freq, int freq2) {
  // Sets the on time and off time for the LED's and writes the HIGH LOW state to the pin.
   currentMillis = millis();
  if ((flashState == 0) && (currentMillis - LEDPrevious1 >= freq)) {
    digitalWrite(LED, LOW);
    flashState++;
    LEDPrevious2 = millis();
  }
  else if ((flashState == 1) && (currentMillis - LEDPrevious2 >= freq2)) {
    digitalWrite(LED, HIGH);
    flashState++;
    LEDPrevious3 = millis();
  }
  else if ((flashState == 2) && (currentMillis - LEDPrevious3 >= freq2)) {
    digitalWrite(LED, LOW);
    flashState++;
    LEDPrevious4 = millis();
  }
  else if ((flashState == 3) && (currentMillis - LEDPrevious4 >= freq2)) {
    digitalWrite(LED, HIGH);
    flashState = 0;
    LEDPrevious1 = millis();
}
}

// TODO: BUG - Sync with host - When host script sends commands one is dropped and arm moves to incorrect pos
String inByte;
int pos;
int counter = 0;
int serVar[] = {90, 20, 25, 130, 50, 180, 180};

void serialEvent() {
// Handle serial commands
  if (Serial.available()) {
    inByte = Serial.readStringUntil('\n');
    pos = inByte.toInt();
    serVar[counter] = pos;
    counter++;
    if (counter >= servoCount) {
      counter = 0;
      Serial.println("Command confirmed... Writing to memory");
      Serial.flush(); // Send bytes to host before continuing.
      moveServo(serVar[0], serVar[1], serVar[2], serVar[3], serVar[4], serVar[5], serVar[6]);
    }
  }
}

// Instructions for basic 3 ball cycle - Down here so script compiles
#include "basicBallCycle.h"

void setup() {
  Serial.begin(115200);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(LASER_EMITTER, OUTPUT);
  digitalWrite(LASER_EMITTER, HIGH);
  pinMode(LIMIT_SWITCH_1, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_2, INPUT_PULLUP);

  // Calibrate Joystick 0 pos // Added in to help correct the sensitive adjustment of the joysticks x & y as well as the play in the z
  JOYSTICK_Z_OFFSET = analogRead(JOYSTICK_Z);
  JOYSTICK_X_OFFSET = analogRead(JOYSTICK_X);
  JOYSTICK_Y_OFFSET = analogRead(JOYSTICK_Y);

  for (int i = servoCount; i >= 0; i--) { // Reverse loop so arm doesnt get damaged if in weird place on board
    servo[i].attach(servoParams[i][PIN]);
    servo[i].write(servoParams[i][CURRENT_POS]); // Send arm to home pos
  }

  digitalWrite(LASER_EMITTER, HIGH);
}

void loop() {
  joystickRead();

  if (analogRead(BALL_DETECTOR) < 512) {
    BALL_DETECTOR_VAL = 1;
    threeBallCycle();
  } else {
    BALL_DETECTOR_VAL = 0;
  }

  flashLED(1000, 60);
    
}
