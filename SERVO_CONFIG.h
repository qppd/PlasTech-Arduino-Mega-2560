#include <Servo.h>

#define SERVO_SIGNAL_PIN 6
#define COIN_SERVO_PIN 33
#define BIN_SERVO_PIN 36

Servo doorServo;
Servo coinServo;
Servo binServo;

void initSERVO() {

  doorServo.attach(SERVO_SIGNAL_PIN);
  doorServo.write(0); 

  coinServo.attach(COIN_SERVO_PIN);
  coinServo.write(0);  

  binServo.attach(BIN_SERVO_PIN);
  binServo.write(0);  
}

void sweepSERVO(int angle, int speed) {
}
