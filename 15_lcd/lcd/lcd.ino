/**
 * Simple LCD demo.
 * 
 * Demonstrates the usage a LCD similar as described here:
 * https://www.arduino.cc/en/Tutorial/HelloWorld
 *  
 * Connections:
 * 
 * Arduino   | LCD
 * --------------------
 * GND       | 1
 * VCC (+5V) | 2
 * POT       | 3
 * 12        | 4
 * GND       | 5
 * 11        | 6
 * 5         | 11
 * 4         | 12
 * 3         | 13
 * 2         | 14
 * VCC (+5V) | 15
 * GND       | 16
 */

// include the library code:
#include <LiquidCrystal.h>

String message1 = "Hello World!";
String message2 = "Welcome!";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // print a message to the LCD.
  // in first line
  lcd.setCursor(0,0);
  lcd.print(message1);

  // in second line
  lcd.setCursor(0,1);
  lcd.print(message2);
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}

