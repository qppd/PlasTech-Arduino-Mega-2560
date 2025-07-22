
#define SERVO_RELAY_PIN 7
#define COIN_RELAY_PIN 34
#define BIN_RELAY_PIN 37

void initRELAY() {
  pinMode(SERVO_RELAY_PIN, OUTPUT);
  digitalWrite(SERVO_RELAY_PIN, HIGH);
  pinMode(COIN_RELAY_PIN, OUTPUT);
  digitalWrite(COIN_RELAY_PIN, HIGH);
  pinMode(BIN_RELAY_PIN, OUTPUT);
  digitalWrite(BIN_RELAY_PIN, HIGH);
}

void operateRELAY(uint16_t RELAY, boolean OPENED) {
  if (OPENED)
    digitalWrite(RELAY, LOW);
  else
    digitalWrite(RELAY, HIGH);
}
