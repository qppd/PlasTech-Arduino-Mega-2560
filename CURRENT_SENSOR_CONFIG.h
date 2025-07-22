#define CURRENT_SENSOR_PIN 42  // Analog input

void initCurrentSensor() {
  pinMode(CURRENT_SENSOR_PIN, INPUT);
}

float readCurrentSensor() {
  int sensorValue = analogRead(CURRENT_SENSOR_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  // For ACS712-20A: 100mV/A, Vcc/2 at 0A
  float current = (voltage - 2.5) / 0.1; // Adjust for your sensor
  return current;
}
