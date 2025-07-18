#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
unsigned long lastPressTime = 0;
const int debounceDelay = 200;

// this function gets called once distance < 10
void printLock() {
  lcd.setCursor(0, 0);
  lcd.print("!!! Obstacle !!!");
  lcd.setCursor(0, 1);
  lcd.print("Device is locked");
}

// handles displayState == 1
// prints data from the ultrasonic sensor
void printUltrasonic() {
  // top line prints "Distance" + the measurement unit
  lcd.setCursor(0, 0);
  lcd.print("Distance");

  // switch distance label between cm and inches
  if(measureState == 0) {
    lcd.print(" (cm):");
  } else {
    lcd.print(" (in):");
  }

  // bottom line prints the distance value + a warning message if distance < 10
  lcd.setCursor(0, 1);
  lcd.print(ultrasonicDistance);

  // prevent errors from staying on screen
  lcd.print("          ");

  if(ultrasonicDistance < 10 && ultrasonicDistance > LOCK_DISTANCE) {
    // warning message if distance < 20
    lcd.setCursor(7, 1);
    lcd.print("Careful!");
  } else {
    // no warning message otherwise
    lcd.setCursor(7, 1);
    lcd.print("          ");
  }
}

// handles displayState == 2
void printPhotoresistor() {
  lcd.setCursor(0, 0);
  lcd.print("Luminosity:");
  lcd.setCursor(0, 1);
  lcd.print(getLuminosity());
  lcd.print("          ");
}

void lcdSetup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void lcdLoop() {
  switch(displayState) {
    case 1:
      printUltrasonic();
      break;
    case 2:
      printPhotoresistor();
      break;
  }
}

#endif