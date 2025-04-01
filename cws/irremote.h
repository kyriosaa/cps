#include <IRremote.h>

#define IR_RECEIVE      5
#define IR_BUTTON_LEFT  8
#define IR_BUTTON_RIGHT 90
#define IR_BUTTON_OK    28
#define IR_BUTTON_STAR  22
#define IR_BUTTON_HASH  13

void irRemoteSetup() {
  IrReceiver.begin(IR_RECEIVE);
}