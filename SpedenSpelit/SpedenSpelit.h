#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>

void initializeTimer(void);

void initializeGame(void);

void checkGame();

void startGame(void);

void endGame(void);

void timerOn(void);

void timerOff(void);

#endif