#include "display.h"
#include "globals.h"
#include <Arduino.h>

const int latchClockPin = 10;
const int shiftDataPin = 8;
const int shiftClockPin = 11;
const int outputEnable = 9;
const int reset = 12;

const byte segmentit[] = {
  B00111111, // 0   "0"         
  B00000110, // 1   "1"        
  B01011011, // 2   "2"         
  B01001111, // 3   "3"         
  B01100110, // 4   "4"         
  B01101101, // 5   "5"         
  B01111101, // 6   "6" 
  B00000111, // 7   "7"         
  B01111111, // 8   "8"
  B01101111, // 9   "9"
};

void initializeDisplay() {
  pinMode(latchClockPin, OUTPUT);
  pinMode(shiftDataPin, OUTPUT);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(outputEnable, OUTPUT);
  pinMode(reset, OUTPUT);
}

// HC595N 8 Bit Shift Registers to shift number of points 
void shiftOutCustom(int shiftDataPin, int shiftClockPin, int bitOrder, byte number) {
  for (int i = 0; i < 8; ++i) {
    digitalWrite(shiftDataPin, (number >> 7-i & 1));
    digitalWrite(shiftClockPin, LOW);
    digitalWrite(shiftClockPin, HIGH);
  }
}

void writeByte(uint8_t number, bool last) {
  digitalWrite(outputEnable, last);  // OutputEnable on before new data
  digitalWrite(latchClockPin, LOW);
  shiftOutCustom(shiftDataPin, shiftClockPin, MSBFIRST, number);
  digitalWrite(latchClockPin, HIGH);
}

void turnDisplayOff() {
  writeByte(0, true);  // 0 on segmentti koodi sammutetulle näytölle
  writeByte(0, false);
}

void showResult(byte result) {

  uint8_t tens = result / 10;
  uint8_t ones = result % 10;
  
  digitalWrite(reset, HIGH);
 
  writeByte(segmentit[ones], true);
  writeByte(segmentit[tens], false); 
}


void newHighScore(int newHighScore) {

  for (int i = 0; i < 5; i++) {
    turnDisplayOff();
    delay(200);
    showResult(newHighScore);
    delay(200);
    }
} 

