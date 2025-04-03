#define PHOTORESISTOR_PIN 0

unsigned long prevMeasure = millis();
unsigned long measureDelay = 100;

int getLuminosity() {
  static unsigned long prevMeasure = 0;
  const unsigned long measureDelay = 100;
  static int luminosityValue = 0;

  if (millis() - prevMeasure >= measureDelay) {
    prevMeasure = millis();
    luminosityValue = analogRead(PHOTORESISTOR_PIN) - 140;
    if (luminosityValue < 0) {
      luminosityValue = 0;
    }
  }
  
  return luminosityValue;
}

void photoresistorSetup() {
  pinMode(PHOTORESISTOR_PIN, OUTPUT);
}