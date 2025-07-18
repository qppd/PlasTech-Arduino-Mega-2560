const uint16_t ULTRASONIC_COUNT = 2;

#define WIDTH_TRIG 23
#define WIDTH_ECHO 24

#define SMALL_TRIG 25
#define SMALL_ECHO 26

#define LARGE_TRIG 27
#define LARGE_ECHO 28



//-----------------------------------------------------------------
//FUNCTION FOR INITIALIZING ULTRASONIC SENSOR ---------------------
//-----------------------------------------------------------------
void initULTRASONIC() {

  pinMode(WIDTH_ECHO, INPUT);
  pinMode(WIDTH_TRIG, OUTPUT);

  pinMode(SMALL_ECHO, INPUT);
  pinMode(SMALL_TRIG, OUTPUT);

  pinMode(LARGE_ECHO, INPUT);
  pinMode(LARGE_TRIG, OUTPUT);
}



//-----------------------------------------------------------------
//FUNCTION FOR DETECTING DISTANCE FROM ULTRASONIC SENSOR ----------
//-----------------------------------------------------------------
int getULTRASONICDistance(uint16_t ULTRASONIC_INDEX) {
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], LOW);  // Clears the trigPin condition
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], HIGH);  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PINS[ULTRASONIC_INDEX], LOW);
  long ultrasonic_duration = pulseIn(ULTRASONIC_ECHO_PINS[ULTRASONIC_INDEX], HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  return ultrasonic_duration * 0.034 / 2;                                            // Speed of sound wave divided by 2 (go and back)
}