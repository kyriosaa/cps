#define PHOTORESISTOR_PIN 0

unsigned long prevMeasure = millis();
unsigned long measureDelay = 100;

// records luminosity value every 100ms
int getLuminosity() {
  static unsigned long prevMeasure = 0;
  const unsigned long measureDelay = 100;
  static int luminosityValue = 0;

  if (millis() - prevMeasure >= measureDelay) {
    prevMeasure = millis();
    luminosityValue = analogRead(PHOTORESISTOR_PIN) - 30;    // -140 to keep value within 250 since LED values go to 255
    if (luminosityValue < 0) {
      luminosityValue = 0;
    }
  }
  
  return luminosityValue;
}

void photoresistorSetup() {
  pinMode(PHOTORESISTOR_PIN, OUTPUT);
}