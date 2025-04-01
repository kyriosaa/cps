#include "ultrasonic.h"
#include "irremote.h"
#include "lcd.h"
#include "button.h"

bool lockState = false;

void setup() {
  Serial.begin(115200);
  
  ultrasonicSetup();
  irRemoteSetup();
  lcdSetup();
}

void loop() {
  if(!lockState) {    // run device as normal if not locked

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
          if(millis() - lastPressTime > debounceDelay) {
            lastPressTime = millis();
            displayState = (displayState % 3) + 1;
          }
          break;
        case IR_BUTTON_LEFT:
          if(millis() - lastPressTime > debounceDelay) {
            lastPressTime = millis();
            displayState = (displayState == 1) ? 3 : displayState - 1;
          }
          break;
        case IR_BUTTON_STAR:
          if(millis() - lastPressTime > debounceDelay) {
            lastPressTime = millis();
            if(displayState == 1) {           // if we are at ultrasonic screen, switch between cm and inches
              if(measureState == 0) {
                lcd.clear();
                measureState = 1;
              } else {
                lcd.clear();
                measureState = 0;
              }
            } else if(displayState == 2) {    // if we are at the reset screen, reset to cm
              measureState = 0;
            }
          }
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

  } else {    // if locked, watch for the push button or the OK button on the remote to be pressed
    printLock();

    if(digitalRead(BUTTON_PIN) == HIGH) {
      lcd.clear();
      lockState = false;
    }

    if(IrReceiver.decode()) {
      IrReceiver.resume();

      int command = IrReceiver.decodedIRData.command;

      if(command == IR_BUTTON_OK) {
        lcd.clear();
        lockState = false;
      }
    }
  }
}
