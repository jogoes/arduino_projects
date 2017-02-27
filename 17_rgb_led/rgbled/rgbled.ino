/**
 * Simple RGB LED demo based on the FastLED library.
 * 
 * Connections:
 * 
 * Arduino   | RGBLED
 * --------------------
 * 6         | DIN
 * GND       | GND
 * VCC (+5V) | 5V
 */
#include "FastLED.h"

// number of LEDs connected in the LED strip
const int NUM_LEDS = 3;
// the Arduino pin the DIN pin of the LED strip should be connected to
const int LED_DATA_PIN = 6;

CRGB leds[NUM_LEDS];

void setup() {
  // initialize library with the number of connected LEDs
  // and the pin the data connection is connected to
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);  
}

void setLED(int n, int r, int g, int b) {
  leds[n].setRGB(r, g, b);  
}

void setLED(int n, const CRGB& color) {
  leds[n] = color;
}

void trafficLights() {
  // RED
  setLED(0, 255, 0, 0); // alternatively use leds[0] = CRGB::Red;
  setLED(1, 0, 0, 0);   // alternatively use leds[1] = CRGB::Black;
  setLED(2, 0, 0, 0);   // alternatively use leds[2] = CRGB::Black;
  FastLED.show();
  delay(1000);
  
  // RED/YELLOW
  setLED(0, 255, 0, 0);
  setLED(1, 255, 255, 0);
  setLED(2, 0, 0, 0);
  FastLED.show();
  delay(1000);

  // GREEN
  setLED(0, 0, 0, 0);
  setLED(1, 0, 0, 0);
  setLED(2, 0, 255, 0);
  FastLED.show();
  delay(1000);

  // YELLOW
  setLED(0, 0, 0, 0);
  setLED(1, 255, 255, 0);
  setLED(2, 0, 0, 0);
  FastLED.show();
  delay(1000);

  // RED
  setLED(0, 255, 0, 0);
  setLED(1, 0, 0, 0)
  setLED(2, 0, 0, 0);
  FastLED.show();
  delay(1000);

  // ALL OFF
  setLED(0, 0, 0, 0);
  setLED(1, 0, 0, 0);
  setLED(2, 0, 0, 0);
  FastLED.show();
  delay(1000);
}

void setColors(int colorStep) {
    int r = colorStep;
    int g = 0;
    int b = 255 - colorStep;

    // fade 1st led from blue to red
    setLED(0, colorStep, 0, 255 - colorStep);
    
    // fade 2nd led from red to green
    setLED(1, colorStep, 255 - colorStep, 0);
    
    // fade 3rd led from blue to yellow
    setLED(2, 255 - colorStep, 255 - colorStep, colorStep);
}

void colorFading() {
  for(int colorStep = 0; colorStep < 256; colorStep++) {

    setColors(colorStep);

    FastLED.show();
    delay(10);
  }
  for(int colorStep = 255; colorStep > 0; colorStep--) {

    setColors(colorStep);

    FastLED.show();
    delay(10);
  }
}

void loop() {
  colorFading();
  trafficLights();  
}

