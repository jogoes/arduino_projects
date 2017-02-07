const int LED_PIN = 6;

void setup() {
}

void loop() {
  analogWrite(LED_PIN, 0);
  delay(1000);
  analogWrite(LED_PIN, 50);
  delay(1000);
  analogWrite(LED_PIN, 255);
  delay(1000);
}
