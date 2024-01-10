#include "buttons.h"
#include "globals.h"

// define pin numbers for buttons
const int pin2 = 2;
const int pin3 = 3;
const int pin4 = 4;
const int pin5 = 5;
const int pin6 = 6;

// this is the function to initialize buttons and set up interrupts
void initButtonsAndButtonInterrupts(void)
{
  // set button pins as input_pullup to enable internal pull-up resistors
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin5, INPUT_PULLUP);
  pinMode(pin6, INPUT_PULLUP);

  // enable pin change interrupts for pins 2-6
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22);

}

// this is the function to read button presses
int readButtonPress(void)
{
  // default state to -1
  int buttonNumber = -1;
  
  // define variables to get current time in ms, incl button press time for debouncing
  unsigned long currentTime = millis();
  static unsigned long lastPressTime = 0;
  const int debounceTime = 250;

  // check if enough time has passed since last button press
  if (currentTime - lastPressTime > debounceTime)
  {
    // check if start button is pressed
    if (digitalRead(pin6) == LOW)
    {
      buttonNumber = 4;
      Serial.println("Start button pressed!");
    }

    // if game is on, check other buttons
    else if (gameStatus == true) 
    {
    
    if (digitalRead(pin2) == LOW)
    {
      buttonNumber = 0;
    }
    if (digitalRead(pin3) == LOW)
    {
      buttonNumber = 1;
    }
    if (digitalRead(pin4) == LOW)
    {
      buttonNumber = 2;
    }
    if (digitalRead(pin5) == LOW)
    {
      buttonNumber = 3;
    }
    }

    // update last press time to current time
    lastPressTime = currentTime;

    // return number of pressed button
    return buttonNumber;
  
  }
}