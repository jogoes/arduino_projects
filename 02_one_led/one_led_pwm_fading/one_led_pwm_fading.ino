const int LED_PIN = 11;

void setup() {
}

void loop() {
  for(int i = 0; i < 255; i+=5) {
    analogWrite(LED_PIN, i);
    delay(20);
  }
  for(int i = 255; i >= 0; i-=5) {
    analogWrite(LED_PIN, i);
    delay(20);
  }
}
