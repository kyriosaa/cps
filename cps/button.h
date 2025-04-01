#define BUTTON_PIN 2

void buttonUnlock() {
  if(digitalRead(BUTTON_PIN) == HIGH) {
    lcd.clear();
    lockState = false;
  }
}

void buttonSetup() {
  pinMode(BUTTON_PIN, INPUT);
}
