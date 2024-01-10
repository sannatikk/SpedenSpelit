#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

void initializeLeds();

void setLed(byte ledNumber);

void clearAllLeds(void);

void setAllLeds(void);

int chooseLed(void);

void blinkLeds(void);

#endif