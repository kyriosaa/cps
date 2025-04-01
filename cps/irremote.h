#include <IRremote.h>

#define IR_RECEIVE      5
#define IR_BUTTON_LEFT  8
#define IR_BUTTON_RIGHT 90
#define IR_BUTTON_OK    28
#define IR_BUTTON_STAR  22
#define IR_BUTTON_HASH  13

void irButtonRight() {
  if(millis() - lastPressTime > debounceDelay) {
    lastPressTime = millis();
    displayState = (displayState % 3) + 1;
  }
}

void irButtonLeft() {
  if(millis() - lastPressTime > debounceDelay) {
    lastPressTime = millis();
    displayState = (displayState == 1) ? 3 : displayState - 1;
  }
}

void irButtonStar() {
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
}

void irButtonOk() {
  if(IrReceiver.decode()) {
    IrReceiver.resume();

    int command = IrReceiver.decodedIRData.command;

    if(command == IR_BUTTON_OK) {
      lcd.clear();
      lockState = false;
    }
  }
}

void irRemoteSetup() {
  IrReceiver.begin(IR_RECEIVE);
}