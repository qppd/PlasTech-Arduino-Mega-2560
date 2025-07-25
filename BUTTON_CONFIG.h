
#define LCD_BUTTON_PIN 50
#define COIN_BUTTON_PIN 49
#define LIMIT_SWITCH_PIN 3


//Inputs and Button Logic
const int numOfInputs = 3;  // number of buttons switches
int inputState[numOfInputs];
int lastInputState[numOfInputs] = { HIGH, HIGH, HIGH };
bool inputFlags[numOfInputs] = { HIGH, HIGH, HIGH };
long lastDebounceTime[numOfInputs] = { 0, 0, 0 };
long debounceDelay = 10;
unsigned long lastActivityTime = 0;  // Tracks last button press time

const int inputPins[numOfInputs] = { LCD_BUTTON_PIN, COIN_BUTTON_PIN, LIMIT_SWITCH_PIN };

void initBUTTONS() {
  for (int i = 0; i < numOfInputs; i++) {  // make switches pin to INPUT and HIGH
    pinMode(inputPins[i], INPUT_PULLUP);
    digitalWrite(inputPins[i], HIGH);
  }
}

void setInputFlags() {

  for (int i = 0; i < numOfInputs; i++) {  // loop until i is less than 4

    int reading = digitalRead(inputPins[i]);  // read pins


    // Serial.print("Pin ");
    // Serial.print(inputPins[i]);
    // Serial.print(" Reading: ");
    // Serial.println(reading);


    if (reading != lastInputState[i]) {  // if reading is not equal to the lastInputState which are (ex: LOW,LOW,LOW,LOW
      lastDebounceTime[i] = millis();    // set lastDebounceTime equal to arduino's running time
    }
    if (millis() - lastDebounceTime[i] > debounceDelay) {  // if arduino's running time and lastDebounceTime difference is greater than debounceDelay whis is 5 then
      if (reading != inputState[i]) {                      // if reading is not equal to inputState ex: 0,0,0,0
        inputState[i] = reading;                           // then make inputState equals to reading

        if (inputState[i] == LOW) {  // if inputState is equal to high which is Pressed switch then
          inputFlags[i] = LOW;       // make inputFlag equal to high
        }
      }
    }
    lastInputState[i] = reading;  // set last Input state equal to reading of every switches
  }                               // loop end
}

void inputAction(int button) {
  Serial.println("Button: " + String(button));

  if (button == 0) {
    Serial.println("LCD Button clicked!");
  } else if (button == 1) {
    Serial.println("COIN Button clicked!");
  } else if (button == 2) {
    Serial.println("LIMIT Switch triggered!");
  } else {
    Serial.println("Unknown Button!");
  }
}


void resolveInputFlags() {
  for (int i = 0; i < numOfInputs; i++) {  // Loop until i is less than 4
    if (inputFlags[i] == LOW) {
      inputAction(i);
      delay(10);
      inputFlags[i] = HIGH;
      lastActivityTime = millis();  // Update last activity time
    }
  }
}
