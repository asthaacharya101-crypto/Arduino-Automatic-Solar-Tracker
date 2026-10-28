#include <Servo.h>

Servo solarServo;

const int LDR1 = A0;
const int LDR2 = A1;
const int SERVO_PIN = 9;

int servoPosition = 90;

const int tolerance = 50;
const int stepSize = 1;
const int moveDelay = 100;

void setup() {
  Serial.begin(9600);

  solarServo.attach(SERVO_PIN);

  servoPosition = 90;
  solarServo.write(servoPosition);

  delay(1000);
}

void loop() {

  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);

  int difference = ldr1 - ldr2;

  Serial.print("LDR1: ");
  Serial.print(ldr1);

  Serial.print(" | LDR2: ");
  Serial.print(ldr2);

  Serial.print(" | Difference: ");
  Serial.println(difference);

  // LDR1 has more light → move toward LDR1
  if (difference > tolerance) {

    if (servoPosition > 0) {
      servoPosition -= stepSize;

      if (servoPosition < 0) {
        servoPosition = 0;
      }

      solarServo.write(servoPosition);
    }
  }

  // LDR2 has more light → move toward LDR2
  else if (difference < -tolerance) {

    if (servoPosition < 180) {
      servoPosition += stepSize;

      if (servoPosition > 180) {
        servoPosition = 180;
      }

      solarServo.write(servoPosition);
    }
  }

  delay(moveDelay);
}
