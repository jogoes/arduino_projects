#include "font8x8.h"

/*
 * A simple POV demo using an array of 8 LEDs.
 * 
 * Connections:
 * Arduino pins 2 to 9 are connected to an LED and a resistor 
 * (typically ~150 to 220 Ohm) and GND on the other end.
 */
 
int firstPin = 2;
int lastPin = 9;

const char* text = "Hallo World ";
const int columnDelayMs = 10;

void setup() {
  // configure LED pins for output
  for(auto i = firstPin; i <= lastPin; i++) {
    pinMode(i, OUTPUT);
  }
}

// write the specified column of the character
// to the LED array
void writeCharColumn(char c, int column) {
  char* charBytes = font8x8_basic[c];
  // get bit of specified column for every row 
  // in the character and set LED to the state of the column
  for(auto row = 0; row < 8; row++) {
    char bit = charBytes[row] >> (7-column);
    digitalWrite(row + firstPin, bit & 1);
  }
}

// iterate through columns of specified character
// and set LED array for every column
void writeChar(char c, int delayInMs) {
  for(auto column = 0; column < 8; column++) {
    writeCharColumn(c, column);
    delay(delayInMs);
  }
}

void loop() {
  for(auto i = 0; i < strlen(text); i++) {
    writeChar(text[i], columnDelayMs);
  }
}
