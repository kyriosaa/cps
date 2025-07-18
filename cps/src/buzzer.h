#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 6

void unlockedBuzzer() {
  static unsigned long lastToggleTime = 0;
  int buzzerDelay = (ultrasonicDistance + 30);

  if(millis() - lastToggleTime >= buzzerDelay) {
    lastToggleTime = millis();
    if(buzzerState == 0) {
      tone(BUZZER_PIN, 1000);
      buzzerState = 1;
    } else {
      noTone(BUZZER_PIN);
      buzzerState = 0;
    }
  }
}

void lockedBuzzer() {
  noTone(BUZZER_PIN);
  buzzerState = 0;
}

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

#endif
