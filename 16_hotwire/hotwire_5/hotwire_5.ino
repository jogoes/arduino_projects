/**
 * The Hotwire game. 
 * 
 * Goal of the game is to guide a wand along a bend wire without touching it.
 * 
 * This is the fourth part of the code. 
 * 
 * Now whenever the wires are getting connected, we are controlling the
 * tone of the sound using the attached potentiometer.
 */

const int LED_GREEN = 9;
const int LED_YELLOW = 10;
const int LED_RED = 11;

const int WAND_PIN = 7;

const int SPEAKER_PIN = 6;

const int POTENTIOMETER_ANALOG_PIN = 0;

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

int touchCount = 0;

void loop() {
  int connected = digitalRead(WAND_PIN);
  if( connected == 1) {
    touchCount++;

    int potValue = analogRead(POTENTIOMETER_ANALOG_PIN);
    int pitch = (potValue * 3) + 300;
    Serial.println(pitch);    
    tone(SPEAKER_PIN, pitch, 200);
    
    // the two wires are connected
    if(touchCount > 10) {
      // turn red LED on if we reached the maximum error count
      setLeds(HIGH, LOW, LOW);
      delay(3000);
      // revert to green and restart after some time
      setLeds(LOW, LOW, HIGH);
      touchCount = 0;
    } else if(touchCount > 5) {
      // turn yellow LED on for some amount of touches
      setLeds(LOW, HIGH, LOW);
    } 

    delay(100);
  }
}
