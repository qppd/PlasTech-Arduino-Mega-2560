#define BTS7960_RPWM 38  // Extension PWM
#define BTS7960_LPWM 39  // Retraction PWM
#define BTS7960_REN 40   // Enable Right
#define BTS7960_LEN 41   // Enable Left

void stopBTS7960();

void initBTS7960() {
  pinMode(BTS7960_RPWM, OUTPUT);
  pinMode(BTS7960_LPWM, OUTPUT);
  pinMode(BTS7960_REN, OUTPUT);
  pinMode(BTS7960_LEN, OUTPUT);
  stopBTS7960();
}

void bts7960Forward(int speed) {
  digitalWrite(BTS7960_REN, HIGH);
  digitalWrite(BTS7960_LEN, HIGH);
  analogWrite(BTS7960_RPWM, constrain(speed, 0, 255));
  analogWrite(BTS7960_LPWM, 0);
}

void bts7960Backward(int speed) {
  digitalWrite(BTS7960_REN, HIGH);
  digitalWrite(BTS7960_LEN, HIGH);
  analogWrite(BTS7960_RPWM, 0);
  analogWrite(BTS7960_LPWM, constrain(speed, 0, 255));
}

void stopBTS7960() {
  digitalWrite(BTS7960_REN, LOW);
  digitalWrite(BTS7960_LEN, LOW);
  analogWrite(BTS7960_RPWM, 0);
  analogWrite(BTS7960_LPWM, 0);
}
