#define CAPACITIVE_SENSOR_PIN 22

void initCapacitiveSensor() {
  pinMode(CAPACITIVE_SENSOR_PIN, INPUT);
}

bool isCapacitiveTouched() {
  return digitalRead(CAPACITIVE_SENSOR_PIN) == HIGH;
}
