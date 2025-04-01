#define RED_LED 12
#define YELLOW_LED 11
#define WHITE_LED 10

#define RED_DELAY 300

void unlockedRed() {
  if(redLedState) {
    redLedState = false;
    digitalWrite(RED_LED, LOW);
  }
}

void unlockedYellow() {
  static unsigned long lastToggleTime = 0;
  int YELLOW_DELAY = (getUltrasonicDistance() + 30);

  if(millis() - lastToggleTime >= YELLOW_DELAY) {
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
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

void lockedYellow() {
  static unsigned long lastToggleTime = 0;

  if(millis() - lastToggleTime >= RED_DELAY) {  // sync blink time with red LED
    lastToggleTime = millis();
    yellowLedState = !yellowLedState;
    digitalWrite(YELLOW_LED, yellowLedState);
  }
}

void ledSetup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
}