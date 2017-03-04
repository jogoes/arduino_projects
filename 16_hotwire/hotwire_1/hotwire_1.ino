/**
 * The Hotwire game. 
 * 
 * Goal of the game is to guide a wand along a bend wire without touching it.
 * 
 * This is the first part in the tutorial.
 * 
 * Here we just turn the three connected LEDs on and off and simulate 
 * traffic lights.
 */

const int LED_GREEN = 9;
const int LED_YELLOW = 10;
const int LED_RED = 11;

// helper function used to set the states of the three
// connected LEDs
void setLeds(int red, int yellow, int green) {
  digitalWrite(LED_RED, red);
  digitalWrite(LED_YELLOW, yellow);
  digitalWrite(LED_GREEN, green);
}

void setup() {
  // initialize the LED pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  // just simulate traffic lights
  setLeds(HIGH, LOW, LOW);
  delay(1000);
  setLeds(HIGH, HIGH, LOW);
  delay(1000);
  setLeds(LOW, LOW, HIGH);
  delay(1000);
  setLeds(LOW, HIGH, LOW);
  delay(1000);
}

