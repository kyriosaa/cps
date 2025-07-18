#include "globals.h"
#include "src/ultrasonic.h"
#include "src/photoresistor.h"
#include "src/lcd.h"
#include "src/irremote.h"
#include "src/button.h"
#include "src/led.h"
#include "src/buzzer.h"
#include <EEPROM.h>

// global variable definitions
bool lockState = false;
int displayState = 1;
int measureState = 0;
int buzzerState = 0;
bool redLedState = false;
bool yellowLedState = false;
double ultrasonicDistance = 1000;

void setup() {
  Serial.begin(115200);
  
  ultrasonicSetup();
  photoresistorSetup();
  irRemoteSetup();
  lcdSetup();
  buttonSetup();
  ledSetup();
  buzzerSetup();

  // read whether to display cm/in from EEPROM memory
  measureState = EEPROM.read(EEPROM_ADDRESS);
}

void loop() {
  if(!lockState) {    // run device as normal if not locked
    // LED
    unlockedRed();
    unlockedYellow();
    unlockedWhite();

    // Buzzer
    unlockedBuzzer();

    // Ultrasonic Sensor 
    ultrasonicLoop();

    // IR Remote 
    irRemoteLoop();

    // LCD Display 
    lcdLoop();

  } else {
    // print lock message on LCD display
    printLock();

    // blinks red LED when device is locked
    lockedRed();
    // syncs yellow LED blink rate to red LED
    lockedYellow();
    // white LED turns off
    lockedWhite();

    lockedBuzzer();

    // unlocks device if push button activates
    buttonUnlock();
    // unlocks device if "OK" is pushed on the ir remote
    irButtonOk();
  }
}
