#include "HX711.h"

#define LOADCELL_DOUT_PIN 29
#define LOADCELL_SCK_PIN 30

HX711 scale;

void initHX711() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(22500.3f);  // Calibrate as needed
  scale.tare();
  Serial.println("HX711 Tare successful");
}

float getHX711Weight() {
  float weight = scale.get_units(10);
  if (weight < 0)
    return 0;
  else
    return weight;
}

void operateHX711sleep() {
  scale.power_down();
}

void operateHX811wake() {
  scale.power_up();
}
