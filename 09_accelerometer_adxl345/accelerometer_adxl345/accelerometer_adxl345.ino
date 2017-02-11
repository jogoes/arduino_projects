/**
 * Simple ADXL345 demo.
 * 
 * Demonstrates the usage of the Adafruit Triple-Axis
 * Accelerometer as e.g. described here:
 * https://www.adafruit.com/product/1231
 * 
 * See the following for an example on how to calibrate the accelerometer:
 * https://learn.adafruit.com/adxl345-digital-accelerometer/programming
 * 
 * Connections:
 * 
 * Arduino | ADXL345
 * -----------------
 * 5V      | VCC
 * GND     | GND
 * SDA     | SDA
 * SCL     | SCL
 */
 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#include "acceleratorinfo.h"

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
 
AcceleratorInfo accelInfo(accel);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Initialising ADXL345 Accelerometer..."); 
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  Serial.println("Initialization done."); 
}

void loop(void)
{
    accelInfo.update();

    Serial.println(accelInfo.toString());
    Serial.println();

    delay(500);
}
