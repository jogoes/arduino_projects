# Contactless Temperature Sensor MLX90614

The [Adafruit MX90614 library](https://github.com/adafruit/Adafruit-MLX90614-Library) makes it simple to use the temperature sensor. 

A tutorial can be found [here](https://learn.adafruit.com/using-melexis-mlx90614-non-contact-sensors/overview).

## Wiring

Wire the sensor with your corresponding board as follows:

### Arduino

|Arduino|MLX90614|
|--|--|
|5V|VIN|
|GND|GND|
|A5|SCL|
|A4|SDA|

### ESP8266

|NodeMCU (ESP8266)|MLX90614|
|--|--|
|3.3V|VIN|
|GND|GND|
|D1|SCL|
|D2|SDA|


### Library Installation
Install the library in the Arduino IDE as follows:
1. go to `Manage Libraries...` 
2. enter `mlx90614` in the `Filter`
3. install the `Adafruit MLX90614 Library`

### Using the 

In the Arduino IDE load the example found under `File/Examples/Adafruit MLX90614 Library/mlxtest`.

Compile and upload the example. Open the `Serial Monitor` window from the Arduino IDE to see the output of the example code.





