#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

void initializeDisplay(void);

void writeByte(uint8_t number, bool last);

void shiftOutCustom(int shiftDataPin, int shiftClockPin, int bitOrder, byte val);

void showResult(byte result);

void turnDisplayOff(void);

void newHighScore(int newHighScore);

void newHighScore(int highScore);


#endif
