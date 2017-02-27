/**
   Simple servo demo.

   Connections:

   Arduino   | Servo
   --------------------
   8         | Signal
   GND       | GND
   VCC (+5V) | 5V
*/
#include <Servo.h>

Servo servo;

int currentAngle = 0;

void setup() {
  servo.attach(8);
  servo.write(0);
}

void rotateServo(int targetAngle, int speed) {
  if(currentAngle < targetAngle) {
    for(int angle = currentAngle; angle < targetAngle; angle++) {
      servo.write(angle);
      delay(speed);
    }
  } else {
    for(int angle = currentAngle; angle > targetAngle; angle--) {
      servo.write(angle);
      delay(speed);
    }
  }
  currentAngle = targetAngle;
}

void loop() {
  rotateServo(90, 15);
  delay(1000);
  rotateServo(0, 15);
  delay(1000);
}

