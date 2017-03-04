const int LED_GREEN = 2;
const int LED_YELLOW = 3;
const int LED_RED = 4;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  digitalWrite(12, HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

void sound(int start, int end) {
  if(start < end) {
    for(int i = start; i < end; i +=10) {
      tone(6, i, 10);
      delay(2);
    }
  } else {
    for(int i = start; i > end; i -=10) {
      tone(6, i, 10);
      delay(2);
    }
  }
}

int touchCount = 0;

void loop() {
  int r = digitalRead(12);
  if( r == 0) {
    touchCount++;
    if(touchCount > 10) {
      digitalWrite(LED_YELLOW, HIGH);      
    }
    if(touchCount > 20) {
      digitalWrite(LED_RED, HIGH);
    }
    digitalWrite(LED_GREEN, LOW);
    sound(440, 1000);
    sound(1000, 440);
    delay(10);
    digitalWrite(LED_GREEN, HIGH);
  }
}
