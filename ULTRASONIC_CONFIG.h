const uint16_t ULTRASONIC_COUNT = 2;

#define WIDTH_TRIG 23
#define WIDTH_ECHO 24

#define SMALL_TRIG 25
#define SMALL_ECHO 26

#define LARGE_TRIG 27
#define LARGE_ECHO 28

#define BOTTLE_CRUSHER_TRIG 43
#define BOTTLE_CRUSHER_ECHO 44
#define COIN_LEVEL_TRIG 45
#define COIN_LEVEL_ECHO 46
#define BIN_LEVEL_TRIG 47
#define BIN_LEVEL_ECHO 48

const int ULTRASONIC_TRIG_PINS[] = {WIDTH_TRIG, SMALL_TRIG, LARGE_TRIG, BOTTLE_CRUSHER_TRIG, COIN_LEVEL_TRIG, BIN_LEVEL_TRIG};
const int ULTRASONIC_ECHO_PINS[] = {WIDTH_ECHO, SMALL_ECHO, LARGE_ECHO, BOTTLE_CRUSHER_ECHO, COIN_LEVEL_ECHO, BIN_LEVEL_ECHO};

//-----------------------------------------------------------------
//FUNCTION FOR INITIALIZING ULTRASONIC SENSOR ---------------------
//-----------------------------------------------------------------
void initULTRASONIC() {
  for (int i = 0; i < 6; i++) {
    pinMode(ULTRASONIC_ECHO_PINS[i], INPUT);
    pinMode(ULTRASONIC_TRIG_PINS[i], OUTPUT);
  }
}

//-----------------------------------------------------------------
//FUNCTION FOR DETECTING DISTANCE FROM ULTRASONIC SENSOR ----------
//-----------------------------------------------------------------
int getULTRASONICDistance(uint16_t ULTRASONIC_INDEX) {
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], LOW);
  long ultrasonic_duration = pulseIn(ULTRASONIC_ECHO_PINS[ULTRASONIC_INDEX], HIGH, 30000);
  return ultrasonic_duration * 0.034 / 2;
}