#include "globals.h"
#include "ultrasonic.h"
#include "lcd.h"
#include "irremote.h"
#include "button.h"
#include "led.h"

void setup() {
  Serial.begin(115200);
  
  ultrasonicSetup();
  irRemoteSetup();
  lcdSetup();
  buttonSetup();
  ledSetup();
}

void loop() {
  if(!lockState) {    // run device as normal if not locked
    // LED -----------------------------------------------------------------------------
    unlockedRed();
    unlockedYellow();
    // ---------------------------------------------------------------------------------

    // Ultrasonic Sensor ---------------------------------------------------------------
    unsigned long timeNow = millis();
    if(timeNow - prevTrigger > triggerDelay) {
      prevTrigger += triggerDelay;
      triggerUltrasonicSensor();
    }
    if(newDistanceAvaliable) {
      newDistanceAvaliable = false;
      double distance = getUltrasonicDistance();
      
      if(distance <= 10) {
        lockState = true;
      }
    }
    // ---------------------------------------------------------------------------------

    // IR Remote -----------------------------------------------------------------------
    if(IrReceiver.decode()) {
      IrReceiver.resume();

      int command = IrReceiver.decodedIRData.command;
      Serial.println(command);
      
      switch(command) {
        case IR_BUTTON_RIGHT:
          irButtonRight();
          break;
        case IR_BUTTON_LEFT:
          irButtonLeft();
          break;
        case IR_BUTTON_STAR:
          irButtonStar();
          break;
      }
    }
    // ---------------------------------------------------------------------------------

    // LCD Display ---------------------------------------------------------------------
    switch(displayState) {
    case 1:
      printUltrasonic();
      break;
    case 2:
      printReset();
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Screen 3");
      lcd.print("          ");
      lcd.setCursor(0, 1);
      lcd.print("          ");
      break;
    // ---------------------------------------------------------------------------------
  }

  } else {
    // print lock message on LCD display
    printLock();
    // blinks red LED when device is locked
    lockedRed();
    // syncs yellow LED blink rate to red LED
    lockedYellow();

    // unlocks device if push button activates
    buttonUnlock();
    // unlocks device if "OK" is pushed on the ir remote
    irButtonOk();
  }
}
