## Capacitive Touch Sensor MPR 121 with Arduino

This project demonstrates the usage of the MPR121 capacitive touch sensor with the Arduino.
See e.g. https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview.

## Capacitive Touch Sensor MPR 121 with S4A and Arduino
This project also demonstrates the usage of the MPR121 capacitive touch sensor with S4A and Arduino.
Corresponding files can be found in the s4a subfolder.

**Important Note:** This project requires the custom firmware as found in here to be uploaded to the Arduino. 
Make sure that wiring of the MPR121 is correct before connecting with S4A, because during setup the firmware 
is initializing the sensor and if this fails S4A will not be able to connect to the Arduino.
