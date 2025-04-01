#define ECHO_PIN 3
#define TRIGGER_PIN 4

int measureState = 0;

unsigned long prevTrigger = millis();
unsigned long triggerDelay = 60;

volatile unsigned long pulseInBegin;
volatile unsigned long pulseInEnd;
volatile bool newDistanceAvaliable = false;

void echoPinInterrupt() {
  if(digitalRead(ECHO_PIN) == HIGH) {
    // rising - start measuring
    pulseInBegin = micros();
  } else {
    // falling - stop measuring
    pulseInEnd = micros();
    newDistanceAvaliable = true;
  }
}

void triggerUltrasonicSensor() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

double getUltrasonicDistance() {
  double durationMicros = pulseInEnd - pulseInBegin;
  if(measureState == 0) {
    double distance = durationMicros / 58.0; // for cm
    return distance;
  } else {
    double distance = durationMicros / 148.0; // for inches
    return distance;
  }
}

void ultrasonicSetup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoPinInterrupt, CHANGE);
}