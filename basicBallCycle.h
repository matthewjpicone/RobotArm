void threeBallCycle() {
  moveServo(90, 20, 25, 130, 50, 180, 180);  // Pick up ball from laser start
  moveServo(48, 139, 143, 140, 28, 180, 180);
  moveServo(48, 139, 143, 135, 28, 135, 135);
  moveServo(48, 125, 150, 135, 64, 135, 135);
  moveServo(48, 50, 25, 180, 180, 135, 135);
  moveServo(129, 60, 25, 180, 180, 135, 135);   // Pick up ball from laser end
  moveServo(129, 90, 27, 156, 175, 135, 135);   // Put ball on 12mm stand
  moveServo(130, 90, 27, 156, 175, 180, 180);   // release ball 12mm - move another degree to centre ball
  moveServo(130, 60, 27, 156, 175, 180, 180);   // retract back
  moveServo(110, 134, 86, 156, 172, 180, 180);  // move to 17mm stand
  moveServo(111, 134, 86, 156, 172, 135, 135);  // grip ball
  moveServo(111, 40, 27, 156, 175, 135, 135);   // retract back
  moveServo(79, 80, 85, 145, 60, 135, 135);     // mid point
  moveServo(47, 138, 143, 135, 30, 135, 135);   // move ball to laser
  moveServo(47, 138, 143, 135, 30, 180, 180);   // release ball on laser
  moveServo(47, 60, 80, 140, 30, 180, 180);
  moveServo(136, 120, 140, 140, 60, 180, 180);  // move to 22mm stand
  moveServo(136, 138, 140, 140, 107, 180, 180);
  moveServo(136, 138, 140, 130, 117, 180, 180);
  moveServo(136, 138, 105, 130, 126, 180, 180);
  moveServo(136, 138, 105, 130, 126, 135, 135);
  moveServo(136, 120, 110, 130, 130, 135, 135);
  moveServo(111, 135, 110, 156, 170, 135, 135);  // move to 17mm stand
  moveServo(111, 125, 87, 156, 170, 135, 135);
  moveServo(111, 125, 74, 156, 170, 135, 135);
  moveServo(111, 125, 74, 156, 170, 180, 180);
  moveServo(111, 90, 90, 156, 170, 180, 180);   // retract from 17mm stand
  moveServo(126, 90, 90, 150, 40, 180, 180);    // move to 12mm stand
  moveServo(126, 113, 100, 130, 40, 180, 180);  // move to 12mm stand
  moveServo(126, 113, 100, 130, 40, 135, 135);
  moveServo(126, 100, 100, 130, 40, 135, 135);
  moveServo(136, 115, 105, 120, 150, 135, 135);  // Move to 22mm Stand
  moveServo(136, 127, 105, 120, 150, 135, 135);  // soften landing
  moveServo(136, 135, 105, 120, 117, 135, 135);
  moveServo(136, 134, 105, 120, 117, 180, 180);
  moveServo(136, 135, 105, 120, 130, 180, 180);
  moveServo(136, 100, 105, 120, 130, 180, 180);
  moveServo(135, 80, 105, 120, 117, 180, 180);
  moveServo(90, 20, 25, 130, 50, 180, 180);
  moveServo(90, 20, 25, 130, 50, 180, 180);
}