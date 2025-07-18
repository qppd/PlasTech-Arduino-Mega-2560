#include "HX711.h"

#define LOADCELL_DOUT_PIN 29
#define LOADCELL_SCK_PIN 30

HX711 scale;

void initHX711() {

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //Serial.print("HX711 RAW: ");
  //Serial.println(scale.read());

  //Serial.print("HX711 AVERAGE: ");
  //Serial.println(scale.read_average(20));  // print the average of 20 readings from the ADC

  //Serial.print("HX711 VALUE: ");
  //Serial.println(scale.get_value(5));  // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  //Serial.print("HX711 UNITS: ");
  //Serial.println(scale.get_units(5), 2);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale.set_scale(22500.3f);  // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("HX711 Tare successful");

  //Serial.print("HX711 RAW: ");
  //Serial.println(scale.read());  // print a raw reading from the ADC

  //Serial.print("HX711 AVERAGE: ");
  //Serial.println(scale.read_average(20));  // print the average of 20 readings from the ADC

  //Serial.print("HX711 VALUE: ");
  //Serial.println(scale.get_value(5));  // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  //Serial.print("HX711 UNITS: ");
  //Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  //Serial.println("Readings:");
}

float getHX711Weight() {
  //Serial.print("one reading:\t");
  //Serial.print(scale.get_units(), 1);
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
