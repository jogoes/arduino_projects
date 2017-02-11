/**
 * Simple HC-SR04 demo.
 * Measures distances using the HC-SR04 sensor
 * and prints it to the serial monitor.
 * 
 * Connections:
 * 
 * Arduino | HC-SR04
 * -----------------
 * 5V      | VCC
 * 11      | Trig
 * 3       | Echo
 * GND     | GND
 */

const int TRIGGER_PIN = 11;
const int ECHO_PIN = 3;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

double getDistanceInMeters() {
  // make sure trigger pin is LOW
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // to start measurement TRIGGER pin of HC-SR04 must receive
  // a pulse of high for at least 10 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // When sensor detected returned signal from receiver,
  // the ECHO pin will be set to HIGH for a period
  // which is proportional to the distance traveled by 
  // the signal. After this the ECHO pin is set to low.

  // pulseIn() waits for pin to go HIGH and returns the
  // time in microseconds after which the pin is set to LOW
  long durationInMicroseconds = pulseIn(ECHO_PIN, HIGH);

  // the returned time is the time for the signal traveling
  // twice the distance (back and forth)
  // take half of this in order to get the duration one-way
  long durationInMicrosecondsOneWay = (durationInMicroseconds/2);

  // speed of sound is assumed to be 340m/s = 0.00034m/1us
  // using this we can calculate the distance (d = v * t) as
  double distanceInMeters = durationInMicrosecondsOneWay * 0.00034;
  return distanceInMeters;  
}

void loop() {
  double distanceInCm = getDistanceInMeters()*100;
  Serial.println(distanceInCm);
}
