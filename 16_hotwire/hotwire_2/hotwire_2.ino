/**
 * The Hotwire game. 
 * 
 * Goal of the game is to guide a wand along a bend wire without touching it.
 * 
 * This is the second part of the code. 
 * 
 * Now whenever the wires are getting connected, we turn on the red LED
 * for some time.
 */

const int LED_GREEN = 9;
const int LED_YELLOW = 10;
const int LED_RED = 11;

const int WAND_PIN = 7;

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

  // initially turn green LED on
  setLeds(LOW, LOW, HIGH);
  
  pinMode(WAND_PIN, INPUT);
}

void loop() {
  int connected = digitalRead(WAND_PIN);
  if( connected == 1) {
    // the two wires are connected
    // turn red led on
    setLeds(HIGH, LOW, LOW);
    // wait for some time...
    delay(500);
    // ... and turn green LED on again
    setLeds(LOW, LOW, HIGH);
  }
}

