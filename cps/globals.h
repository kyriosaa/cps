#ifndef GLOBALS_H
#define GLOBALS_H

// global constants
#define LOCK_DISTANCE 3
#define EEPROM_ADDRESS 0

// global variable declarations (extern means defined elsewhere)
extern bool lockState;
extern int displayState;
extern int measureState;
extern int buzzerState;
extern bool redLedState;
extern bool yellowLedState;
extern double ultrasonicDistance;

#endif