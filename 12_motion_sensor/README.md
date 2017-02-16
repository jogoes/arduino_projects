## PIR (motion detection sensor) with Arduino

Demonstrates the usage a PIR sensor similar to the one described here:
https://www.adafruit.com/product/189

Connections:

| Arduino   | RFID
------------|---------
| A2        | OUT
| GND       | GND
| VCC (+5V) | VIN

Note, that this example uses an analog pin for input.
The reason is to make it easier to use with Scratch for Arduino
(see the project in this directory).

When you have full control over the code running on Arduino
it's recommended to use a digital pin for input. The Arduino sketch is already
prepared for this. Change the code according to your needs.