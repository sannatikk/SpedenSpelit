#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "globals.h"

// global variables

volatile int points = 0;
volatile int highScore = 0;
volatile int gameStatus = true;

volatile int ledNumberArray[100];
volatile int buttonPressArray[100];

volatile int pressedButton;

// counter variables
volatile int k;
volatile int l;
volatile int j;

void setup()
{
  Serial.begin(9600);

  // initialize modules
  initButtonsAndButtonInterrupts();
  initializeLeds(); 
  initializeDisplay(); 
  initializeTimer(); // (note: timer interrupts off until game starts)

}

void loop()
{
  
  // show points from very beginning
  if ( points == 0) {
   showResult(points); 
  }

  // if start button is pressed, blink leds and start game
  if ( pressedButton == 4 ) {
    blinkLeds();
    startGame();
  }

  // if game is active and player presses game button, add press to array and check whether correct
  if (gameStatus == true) {
      if (pressedButton >= 0 && pressedButton < 4) {
        buttonPressArray[points] = pressedButton;
        checkGame();
        pressedButton = -1;
      }
  }
}

void initializeTimer(void) {

  // interrupts off during setup
  noInterrupts();

  // normal mode
  TCCR1A = 0;

  // wgm12 on -> CTC mode, prescaler 1024
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10) | (1 << CS12);
  
  // 1Hz interrupts to start with
  OCR1A = 15624;

  // output compare interrupt enable 1a
  // this bit set to 0 until we want to enable timer interrupts from the timerOn function
  TIMSK1 |= (0 << OCIE1A); 

  // interrupts back on
  interrupts();

}

void startGame() {

  // resets global variables, points, and arrays
  initializeGame();  
  
  // timer interrupts on
  timerOn();

  // all leds should be off but turning them off manually here just in case
  clearAllLeds();

  // game is active
  gameStatus = true;

  Serial.println("Game on!");

  // leds start blinking now, game has started

}

void initializeGame() {
  // this is called from startGame()
  
  // reset points
  points = 0;

  // loop through arrays and reset values to -1
  
  for (int i=0; i<100; i++) {
    ledNumberArray[i] = -1;
  }

  for (int i = 0; i<100; i++) {
    buttonPressArray[i] = -1;
  }

  // reset button press
  pressedButton = -1;

  // this to deal with first randomly fast timer interrupt
  k = -1;
  // this to keep track of place in led number array 
  l = 0;
  // this to keep track of timer interrupt acceleration 
  j = 0;

}

ISR(TIMER1_COMPA_vect) {
  // this happens every time a timer overflow interrupt happens 
  // --> produces number for led, lights led, and adds number to led number array

  int ledNumber = chooseLed();
  
  // net to catch bugs
  if (ledNumber == -1) {
    return;
  }

  // add led number to array
  ledNumberArray[l] = ledNumber;

  // send generated number to setLed()
  setLed(ledNumber);

  // one element forward in array
  l++;

  // increase timer overflow interrupts by 10% every fifth interrupt
  j++;
  if (j==6) {
    OCR1A = OCR1A * 0.9;
    j = 0;
  }
  
}

ISR(PCINT2_vect) {

  // this function handles button press interruts and sends to main loop
  
  // button that caused interrupt
  int buttonNumber = readButtonPress();

  // if something goes wrong and function returns -1, nope out
  if (buttonNumber == -1) {
    return;
  }
  
  // if all is well, save into global variable to be handled in main loop
  pressedButton = buttonNumber;

}

void checkGame(void) {

  // if pressed button is the same as the number in led number array --> points++
  // if pressed button was wrong --> call endGame() which disables timer interrupts and sends high score to display

  if (ledNumberArray[points] == -1) {
    return;
  }

  if ( buttonPressArray[points] == ledNumberArray[points] ) {

    points++;

    showResult(points);
    
  }

  else {

    endGame();
  }

}

void endGame() {

  Serial.println("Game over!");

  // disable timer interrupts -> leds no longer blink, numbers no longer added to arrays
  timerOff();

  // game status off, program no longer handles interrupts from buttons 0-3
  gameStatus = false; 

  // blink leds to indicate end of game
  blinkLeds();

  // check if new high score
  // if yes --> update and send to blink on display
  if (points > highScore) {
    highScore = points;
    newHighScore(highScore); 
  }

  Serial.print("Your points: ");
  Serial.println(points);
  Serial.print("High score: ");
  Serial.println(highScore);

}

void timerOn() {

  // compare interrupts on
  TIMSK1 |= (1 << OCIE1A); 

  // reset interrupts to 1Hz
  OCR1A = 15624;

}

void timerOff() {

  // compare interrupts off
  TIMSK1 &= (0 << OCIE1A); 

}
