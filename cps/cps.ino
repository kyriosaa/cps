#include "globals.h"
#include "ultrasonic.h"
#include "photoresistor.h"
#include "lcd.h"
#include "irremote.h"
#include "button.h"
#include "led.h"
#include "buzzer.h"

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
