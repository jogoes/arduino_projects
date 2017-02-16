/**
 * Simple motion sensor demo.
 * 
 * Demonstrates the usage a PIR sensor similar to the one described here:
 * https://www.adafruit.com/product/189
 *  
 * Connections:
 * 
 * Arduino   | RFID
 * --------------------
 * A2        | OUT
 * GND       | GND
 * VCC (+5V) | VIN
 * 
 * Note, that this example uses an analog pin for input.
 * The reason is to make it easier to use with Scratch for Arduino
 * (see the project in this directory).
 * 
 * When you have full control over the code running on Arduino
 * it's recommended to use a digital pin for input.
 * The code below allows both possibilities.
 */

const int ANALOG_INPUT_PIN = A2;
const int DIGITAL_INPUT_PIN = 10;

void setup()  
{
  Serial.begin(9600);

  // comment/uncomment depending on analog/digital pin usage
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DIGITAL_INPUT_PIN, INPUT);
}

int previousState = 0;

void loop() {
  // comment/uncomment depending on analog/digital pin usage
  //int state = analogRead(ANALOG_INPUT_PIN) > 0 ? 1 : 0;
  int state = digitalRead(DIGITAL_INPUT_PIN);
  
  if(previousState != state) {
    // do something only when state has changed
    if(state > 0) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("MOVEMENT DETECTED");
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("STATE RESET");
    }
    previousState = state;
  }
}

