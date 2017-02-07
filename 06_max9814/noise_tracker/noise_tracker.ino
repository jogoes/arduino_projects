
const int LED_RED = 11;
const int LED_YELLOW = 12;
const int LED_GREEN = 13;

const int AMPLIFIER_PIN = A5;

// Sample window width in milliseconds (50 mS = 20Hz)
const int SAMPLE_WINDOW_MS = 50; 
// the maximum difference between minimum and maximum noise level
const int MAX_AMPLIFIER_VALUE = 500; 
 
void setup() 
{  
}

// returns the difference between the minimum and maximum signal
// recorded by the amplifier during the specified period in milliseconds
// we take the difference in order to eliminate the permanent noise level
unsigned int sampleSignal(int sampleWindowMs) {
  unsigned long startMs = millis();
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while(millis() - startMs < sampleWindowMs) {
    unsigned int sample = analogRead(AMPLIFIER_PIN);
    if(sample < 1024) { // eliminate spikes
      signalMax = max(signalMax, sample);
      signalMin = min(signalMin, sample);
    }    
  }

  return signalMax - signalMin;
}
 
void loop() 
{
   unsigned long noiseLevel = sampleSignal(SAMPLE_WINDOW_MS);
   analogWrite(LED_RED, min(255, noiseLevel * 255 / MAX_AMPLIFIER_VALUE));
}

