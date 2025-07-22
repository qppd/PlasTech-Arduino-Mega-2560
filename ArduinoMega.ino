#include "BTS7960_CONFIG.h"
#include "BUTTON_CONFIG.h"
#include "CAPACITIVE_CONFIG.h"
#include "CURRENT_SENSOR_CONFIG.h"
#include "L298N_CONFIG.h"
#include "LCD_CONFIG.h"
#include "LED_CONFIG.h"
#include "LIMIT_SWITCH_CONFIG.h"
#include "LOADCELL_CONFIG.h"
#include "RELAY_CONFIG.h"
#include "SERIAL_CONFIG.h"
#include "SERVO_CONFIG.h"
#include "TCTRT5000_CONFIG.h"
#include "ULTRASONIC_CONFIG.h"

// State machine for stages
enum Stage {
  STAGE_POWER_OFF = 0,
  STAGE_CAP_DETECTION = 1,
  STAGE_MEASUREMENT = 2,
  STAGE_CRUSHER = 3,
  STAGE_SECOND_MEASUREMENT = 4,
  STAGE_COIN_DISPENSE = 5
};

Stage currentStage = STAGE_POWER_OFF;
bool lcdPower = false;
int smallBottleCount = 0;
int bigBottleCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Arduino Mega 2560");
  initBTS7960();
  initL298N();
  initLCD();
  initLED();
  initLIMITSwitch();
  initHX711();
  initRELAY();
  initSERIAL();
  initSERVO();
  initTCTRT5000();
  initULTRASONIC();
  initCapacitiveSensor();
  initCurrentSensor();
  // BUTTON_CONFIG.h does not have a single init function
  turnLCDBacklight(false);
}

void loop() {
  switch (currentStage) {
    case STAGE_POWER_OFF:
      // Stage 0: Wait for LCD power button
      if (digitalRead(LCD_BUTTON_PIN) == LOW) {
        turnLCDBacklight(true);
        clearLCD();
        setLCDText("System Powered ON", 0, 0);
        turnLED(GREEN_LED_PIN, true);
        lcdPower = true;
        delay(2000);
        clearLCD();
        setLCDText("Waiting Bottle...", 0, 0);
        turnLED(GREEN_LED_PIN, false);
        currentStage = STAGE_CAP_DETECTION;
      } else {
        turnLCDBacklight(false);
        turnLED(RED_LED_PIN, false);
        turnLED(GREEN_LED_PIN, false);
      }
      break;

    case STAGE_CAP_DETECTION:
      // Stage 1: Wait for limit switch (start trigger)
      if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
        clearLCD();
        setLCDText("Checking for cap...", 0, 0);
        delay(500);
        int irValue = digitalRead(IR_SENSOR_PIN);
        if (irValue == LOW) {
          // Cap detected
          turnLED(RED_LED_PIN, true);
          turnLED(GREEN_LED_PIN, false);
          clearLCD();
          setLCDText("Please remove", 0, 0);
          setLCDText("bottle cap", 0, 1);
        } else {
          // No cap detected
          turnLED(RED_LED_PIN, false);
          turnLED(GREEN_LED_PIN, true);
          clearLCD();
          setLCDText("No Cap Detected", 0, 0);
          setLCDText("Opening Door...", 0, 1);
          operateRELAY(SERVO_RELAY_PIN, true); // Power servo
          delay(100);
          doorServo.write(0); // Open door
          delay(3000);
          doorServo.write(180); // Close door
          delay(500);
          operateRELAY(SERVO_RELAY_PIN, false); // Power off servo
          turnLED(GREEN_LED_PIN, false);
          clearLCD();
          setLCDText("Insert Bottle...", 0, 0);
          currentStage = STAGE_MEASUREMENT;
        }
        delay(1500);
        // Wait for limit switch release
        while (digitalRead(LIMIT_SWITCH_PIN) == LOW);
        delay(300);
      }
      break;

    case STAGE_MEASUREMENT:
      // Stage 2: Measurement
      if (isCapacitiveTouched()) {
        clearLCD();
        setLCDText("Plastic Detected", 0, 0);
        doorServo.write(180); // Close door
        delay(500);
        // Measure bottle
        int width = getULTRASONICDistance(0); // WIDTH
        int smallHeight = getULTRASONICDistance(1); // SMALL HEIGHT
        int largeHeight = getULTRASONICDistance(2); // LARGE HEIGHT
        float weight = getHX711Weight();
        bool smallDetected = (smallHeight < 100 && width < 100); // Adjust threshold
        bool bigDetected = (smallHeight < 100 && largeHeight < 100); // Adjust threshold
        clearLCD();
        setLCDText("Width:", 0, 0); setLCDText(width, 7, 0);
        setLCDText("S:", 0, 1); setLCDText(smallHeight, 3, 1);
        setLCDText("L:", 8, 1); setLCDText(largeHeight, 10, 1);
        setLCDText("Weight:", 0, 2); setLCDText(weight, 8, 2);
        delay(1000);
        if (smallDetected && weight >= 9 && weight <= 15) {
          smallBottleCount++;
          clearLCD();
          setLCDText("Small Bottle OK", 0, 0);
          turnLED(GREEN_LED_PIN, true);
          rotateCW(200); // Accept
          delay(3000);
          stopMotor();
          turnLED(GREEN_LED_PIN, false);
          currentStage = STAGE_CRUSHER;
        } else if (bigDetected && weight >= 33 && weight <= 44) {
          bigBottleCount++;
          clearLCD();
          setLCDText("Big Bottle OK", 0, 0);
          turnLED(GREEN_LED_PIN, true);
          rotateCW(200); // Accept
          delay(3000);
          stopMotor();
          turnLED(GREEN_LED_PIN, false);
          currentStage = STAGE_CRUSHER;
        } else {
          turnLED(RED_LED_PIN, true);
          clearLCD();
          setLCDText("Rejected!", 0, 0);
          setLCDText("Opening Door", 0, 1);
          doorServo.write(0); // Open door
          delay(2000);
          rotateCCW(200); // Reject
          delay(3000);
          stopMotor();
          doorServo.write(180); // Close door
          delay(500);
          turnLED(RED_LED_PIN, false);
          currentStage = STAGE_CAP_DETECTION;
        }
        delay(1500);
      }
      break;

    case STAGE_CRUSHER:
      // Stage 3: Bottle Crusher
      clearLCD();
      setLCDText("Crushing...", 0, 0);
      bts7960Forward(200); // Extend actuator
      delay(4000); // Adjust as needed
      float current = readCurrentSensor();
      if (current > 2.0) { // Stall detected, adjust threshold
        stopBTS7960();
        delay(1000);
        bts7960Backward(200); // Retract actuator
        delay(4000);
        stopBTS7960();
        clearLCD();
        setLCDText("Crushed!", 0, 0);
        delay(1000);
        currentStage = STAGE_SECOND_MEASUREMENT;
      } else {
        stopBTS7960();
        currentStage = STAGE_SECOND_MEASUREMENT;
      }
      break;

    case STAGE_SECOND_MEASUREMENT:
      // Stage 4: Second measurement (width after crushing)
      int widthAfter = getULTRASONICDistance(0); // WIDTH
      clearLCD();
      setLCDText("Width After:", 0, 0);
      setLCDText(widthAfter, 13, 0);
      delay(1000);
      // Open bin door
      operateRELAY(BIN_RELAY_PIN, true);
      delay(100);
      binServo.write(0); // Open
      delay(2000);
      binServo.write(180); // Close
      delay(500);
      operateRELAY(BIN_RELAY_PIN, false);
      clearLCD();
      setLCDText("Ready for next", 0, 0);
      delay(1000);
      currentStage = STAGE_COIN_DISPENSE;
      break;

    case STAGE_COIN_DISPENSE:
      // Stage 5: Coin dispenser
      clearLCD();
      setLCDText("Press Coin Btn", 0, 0);
      if (digitalRead(COIN_BUTTON_PIN) == LOW) {
        operateRELAY(COIN_RELAY_PIN, true);
        delay(100);
        coinServo.write(0);
        delay(1000);
        coinServo.write(180);
        delay(500);
        operateRELAY(COIN_RELAY_PIN, false);
        clearLCD();
        setLCDText("Coin Dispensed", 0, 0);
        delay(2000);
        // Show bottle counts
        clearLCD();
        setLCDText("Small:", 0, 0); setLCDText(smallBottleCount, 7, 0);
        setLCDText("Big:", 0, 1); setLCDText(bigBottleCount, 7, 1);
        delay(3000);
        // Reset for next user
        smallBottleCount = 0;
        bigBottleCount = 0;
        currentStage = STAGE_POWER_OFF;
      }
      break;
  }
}

