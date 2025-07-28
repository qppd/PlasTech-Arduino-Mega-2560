#include <Servo.h>

#define SERVO_SIGNAL_PIN 6 // gumana
#define COIN_SERVO_PIN 33
#define BIN_SERVO_PIN 36 //

Servo doorServo;
Servo coinServo;
Servo binServo;

int currentDoorAngle = 0;
int currentCoinAngle = 0;
int currentBinAngle = 0;

void initSERVO() {
  doorServo.attach(SERVO_SIGNAL_PIN);
  doorServo.write(0);
  coinServo.attach(COIN_SERVO_PIN);
  coinServo.write(0);
  binServo.attach(BIN_SERVO_PIN);
  binServo.write(0);
}

void operateSERVO(Servo &servo, int &currentAngle, int targetAngle, int speed) {
  if (currentAngle == targetAngle) return;

  int step = (currentAngle < targetAngle) ? 1 : -1;

  for (int pos = currentAngle; pos != targetAngle; pos += step) {
    servo.write(pos);
    delay(speed);  // speed controls smoothness
  }

  servo.write(targetAngle);  // ensure final position is reached
  currentAngle = targetAngle;
}
