#define RED_LED 12
#define YELLOW_LED 11
#define WHITE_LED 10

#define RED_DELAY 300

// Red LED -------------------------------------------------------
void unlockedRed() {
  if(redLedState) {
    redLedState = false;
    digitalWrite(RED_LED, LOW);
  }
}

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
void unlockedYellow() {
  static unsigned long lastToggleTime = 0;
  int yellowDelay = (getUltrasonicDistance() + 30);

  if(millis() - lastToggleTime >= yellowDelay) {
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
  }
}

void lockedYellow() {
  static unsigned long lastToggleTime = 0;

  if(millis() - lastToggleTime >= RED_DELAY) {  // sync blink time with red LED
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
  }
}
// ---------------------------------------------------------------

// White LED -----------------------------------------------------
void unlockedWhite() {
  int photoresistorValue = getLuminosity();
  int whiteBrightness = photoresistorValue / 2;

  analogWrite(WHITE_LED, whiteBrightness);
}

void lockedWhite() {
  digitalWrite(WHITE_LED, LOW);
}
// ---------------------------------------------------------------

void ledSetup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
}