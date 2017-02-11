## Arduino and ADXL345 accelerometer

Contains some simple Arduino code demonstrating the usage of the ADXL345
accelerometer as provided by Adafruit. Product info can be found here:
https://www.adafruit.com/product/1231

## Accelerometer with S4A and Arduino

The s4a folder contains the corresponding files demonstrating the usage of an ADXL345 accelerometer (e.g. https://learn.adafruit.com/adxl345-digital-accelerometer)
with S4A and Arduino. A small scratch project is provided showing how to control a sprite by turning and tilting the accelerometer. 

**Important Note:** This project requires the custom firmware as found in here to be uploaded to the Arduino.
This firmware is derived from the standard S4A firmware and provides S4A with information about
https://www.adafruit.com/product/1231the orientation of the sensor. The orientation is returned as values with a range from 0 to 180 degrees 
in the Analog3 (X axis) and Analog4 (Y axis) inputs within S4A.
