/**
 * Simple MPR121 demo.
 * 
 * 
 * Demonstrates the usage of the Adafruit MPR121 capacitive touch sensor
 * as e.g. described here:
 * https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview
 * 
 * Requires the Adafruit MPR121 library to be installed. See the above link 
 * for detailed instructions on how to do this.
 * 
 * Code below is inspired by the MPR121test example provided by Adafruit.
 * 
 * Connections:
 * 
 * Arduino | MPR121
 * -----------------
 * 5V      | VIN
 * GND     | GND
 * A4      | SDA
 * A5      | SCL
 */
 
#include <Wire.h>
#include "Adafruit_MPR121.h"

#include "mpr121util.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

MPR121Helper mpr121(cap);

// forward declarations
void onTouched(uint8_t);
void onReleased(uint8_t);

void setup() {
  while (!Serial);        // needed to keep leonardo/micro from starting too fast!

  Serial.begin(9600);
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  mpr121.registerOnTouched(onTouched);
  mpr121.registerOnReleased(onReleased);
}

void onTouched(uint8_t pin) {
  Serial.println(String(pin) + String(" touched"));
}

void onReleased(uint8_t pin) {
  Serial.println(String(pin) + String(" released"));
}

void loop() {

  mpr121.update();

  // comment out this line for detailed data from the sensor!
  return;

  mpr121.printDebugInfo();
}



