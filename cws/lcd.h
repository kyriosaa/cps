#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
int displayState = 1;
unsigned long lastPressTime = 0;
const int debounceDelay = 200;

// this function gets called once distance < 10
void printLock() {
  lcd.setCursor(0, 0);
  lcd.print("!!! Obstacle !!!");
  lcd.setCursor(0, 1);
  lcd.print("Device is locked");
}

void printUltrasonic() {
  lcd.setCursor(0, 0);
  lcd.print(getUltrasonicDistance());

  // switch between cm and inches
  if(measureState == 0) {
    lcd.print(" cm");
  } else {
    lcd.print(" inches");
  }

  // prevent errors from staying on screen
  lcd.print("          ");

  if(getUltrasonicDistance() < 20 && getUltrasonicDistance() > 10) {
    // warning message if distance < 20
    lcd.setCursor(0, 1);
    lcd.print("Careful!");
  } else {
    // no warning message otherwise
    lcd.setCursor(0, 1);
    lcd.print("          ");
  }
}

void printReset() {
  lcd.setCursor(0, 0);
  lcd.print("Press * to reset");
  lcd.setCursor(0, 1);
  lcd.print("to default");
  lcd.print("          ");
}

void lcdSetup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}