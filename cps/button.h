#define BUTTON_PIN 2

// allows for the device to be unlocked through the push button
void buttonUnlock() {
  if(digitalRead(BUTTON_PIN) == HIGH) {
    lcd.clear();
    lockState = false;
  }
}

void buttonSetup() {
  pinMode(BUTTON_PIN, INPUT);
}
