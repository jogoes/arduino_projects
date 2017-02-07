const int SENSOR_PIN = A0;
const int LED_PIN = 11;

void setup() {
  Serial.begin(9600);
}

long sensorValue = 0;

void loop() {
  sensorValue = analogRead(SENSOR_PIN);
  analogWrite(LED_PIN, (sensorValue * 255) / 1024);
  delay(30);
}
