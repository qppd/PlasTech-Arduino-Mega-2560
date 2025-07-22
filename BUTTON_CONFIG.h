
#define LCD_BUTTON_PIN 8
#define COIN_BUTTON_PIN 9

//Inputs and Button Logic
const int numOfInputs = 2;  // number of buttons switches
int inputState[numOfInputs];
int lastInputState[numOfInputs] = { HIGH, HIGH };
bool inputFlags[numOfInputs] = { HIGH, HIGH };
long lastDebounceTime[numOfInputs] = { 0, 0 };
long debounceDelay = 10;

const int inputPins[numOfInputs] = { LCD_BUTTON_PIN, COIN_BUTTON_PIN };


void setInputFlags() {
  for (int i = 0; i < numOfInputs; i++) {
    int reading = digitalRead(inputPins[i]);
    if (reading != lastInputState[i]) {
      lastDebounceTime[i] = millis();
    }
    if (millis() - lastDebounceTime[i] > debounceDelay) {
      if (reading != inputState[i]) {
        inputState[i] = reading;
        if (inputState[i] == LOW) {
          inputFlags[i] = LOW;
        }
      }
    }
    lastInputState[i] = reading;
  }
}
void resolveInputFlags() {
  for (int i = 0; i < numOfInputs; i++) {
    if (inputFlags[i] == LOW) {
      // inputAction(i); // Commented out, not defined
      delay(10);
      inputFlags[i] = HIGH;
      // lastActivityTime = millis(); // Commented out, not defined
    }
  }
}