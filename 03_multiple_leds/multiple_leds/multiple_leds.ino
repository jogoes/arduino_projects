const int LED_PIN1 = 12;
const int LED_PIN2 = 13;

void setup() {
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN1, HIGH);
  digitalWrite(LED_PIN2, LOW);
  delay(500);
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, HIGH);
  delay(500);
}
