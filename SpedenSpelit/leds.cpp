#include "leds.h"
#include "globals.h"


void initializeLeds() {

  // sets correct pins ot output for leds
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

}

void setLed(byte ledNumber) {

  // clears all leds and sets the one specified

  int ledPin = A2 + ledNumber;

  clearAllLeds();
  digitalWrite(ledPin, HIGH);

}

void clearAllLeds() {

  // all leds off

  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
 
}

void setAllLeds() {

  // all leds on

  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);

}

int chooseLed() {

  // variable for led number
  volatile int number;
 
  // if this is first unpredictably fast timer interrupt of game, ignore it
  if (k == -1) {
    k=0;
    return;
  }

  // take value from a0 pin to give as parameter to randomSeed()
  if (l==0) {
  int randomValue = analogRead(A0);
  randomSeed(randomValue);
  }

  // generate value between 0-3
  number = random(4);

  // same led can't blink twice in a row -> if we are on first element, let it be; if we are in place 1+, check that the number isn't the same as the previous one
  // if it is the same, shift it by one
  if (l == 0) {
    return number;
  }

  while (ledNumberArray[l-1] == number) {
      number = random(4);
    }

  return number;

}

void blinkLeds(void) {

  // blink all leds 3 times for 100ms
  
  for ( int i=0; i<3; i++ ) {
  setAllLeds();
  delay(100);
  clearAllLeds();
  delay(100);
  }
}