# SpedenSpelit

Oulu University of Applied Sciences "Tietotekniikan sovellusprojekti" (Applied Information Technology Project), 1st year 1st semester student project!

Arduino project "Speden Spelit" has 4 LEDs and 5 buttons (4 GAMEPLAY buttons, 1 START button), and two 7 segment displays. When the start button is pressed, the LEDs will start blinking at a 1Hz frequency. The user has to press the respective gameplay buttons in correct order. The LED blinking frequency will increase by 10% every 6th blink. The 7 segment displays will keep track of the player's current score, a.k.a. correct gameplay button presses since the game started. When the player fails to press the correct button, the game will end and LEDs will stop blinking. If the player has achieved a HIGH SCORE since Arduino reset, the 7 segment display will blink to signal this. Otherwise the score will remain static on the display until start button is pressed again.

"Buttons" and "Display" files made in collaboration with fellow students Sanna Koukkula and Eerika Pölkky.
