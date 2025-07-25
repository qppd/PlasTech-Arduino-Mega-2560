#define CURRENT_SENSOR_PIN A0
#define NUM_SAMPLES 50  // Number of samples for averaging

void initCurrentSensor() {
  pinMode(CURRENT_SENSOR_PIN, INPUT);
}

float readCurrentSensor() {
  long total = 0;

  // Read multiple samples
  for (int i = 0; i < NUM_SAMPLES; i++) {
    total += analogRead(CURRENT_SENSOR_PIN);
    delayMicroseconds(200);  // Small delay for ADC stability (optional)
  }

  // Compute the average sensor value
  float averageSensorValue = total / (float)NUM_SAMPLES;

  // Convert to voltage
  float voltage = averageSensorValue * (5.0 / 1023.0);

  // Calibrated formula for ACS712-20A
  float current = (voltage - 2.5) / 0.08;

  // Optional: Remove negative noise
  if (current < 0)
    return 0;

  return current;
}
