#include "Arduino.h"
#define IR_SENSOR_PIN 2


void initTCTRT5000() {
  pinMode(IR_SENSOR_PIN, INPUT);
}

int checkBOTTLECap() {

  return digitalRead(IR_SENSOR_PIN);
}
