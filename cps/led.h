#define RED_LED 12
#define YELLOW_LED 11
#define WHITE_LED 10

#define RED_DELAY 300

// Red LED -------------------------------------------------------

// when device is unlocked, turn off red LED
void unlockedRed() {
  if(redLedState) {
    redLedState = false;
    digitalWrite(RED_LED, LOW);
  }
}

// when device is locked, blink red LED every 300ms
void lockedRed() {
  static unsigned long lastToggleTime = 0;

  if(millis() - lastToggleTime >= RED_DELAY) {
    lastToggleTime = millis();
    redLedState = !redLedState;
    digitalWrite(RED_LED, redLedState);
  }
}

// ---------------------------------------------------------------

// Yellow LED ----------------------------------------------------

// when device is unlocked, blink yellow LED according to the distance value
void unlockedYellow() {
  static unsigned long lastToggleTime = 0;
  int yellowDelay = (getUltrasonicDistance() + 30);

  if(millis() - lastToggleTime >= yellowDelay) {
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
  }
}

// when device is locked, sync blink rate with red LED
void lockedYellow() {
  static unsigned long lastToggleTime = 0;

  if(millis() - lastToggleTime >= RED_DELAY) {  // sync blink rate with red LED
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
  }
}
// ---------------------------------------------------------------

// White LED -----------------------------------------------------

// when device is unlocked, set brightness value of white LED to the photoresistor value
void unlockedWhite() {
  int photoresistorValue = getLuminosity();
  int whiteBrightness = photoresistorValue / 2;

  analogWrite(WHITE_LED, whiteBrightness);
}

// when device is locked, turn off white LED (no state needed since white LED's function is analog)
void lockedWhite() {
  digitalWrite(WHITE_LED, LOW);
}
// ---------------------------------------------------------------

void ledSetup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
}