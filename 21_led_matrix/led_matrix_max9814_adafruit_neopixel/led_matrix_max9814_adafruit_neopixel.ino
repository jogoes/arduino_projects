#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "textscroller.h"
#include "scrollingchart.h"

const int DATA_PIN = 6;

const int AMPLIFIER_PIN = A5;

// Sample window width in milliseconds (50 mS = 20Hz)
const int SAMPLE_WINDOW_MS = 30; 
// the maximum difference between minimum and maximum noise level
const int MAX_AMPLIFIER_VALUE = 510; 

const int MIN_THRESHOLD = 30;

// initialize matrix with the coordinate (0,0) being in the top left corner

/*
// use this for "portrait mode"
const int WIDTH = 16;
const int HEIGHT = 20;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, DATA_PIN,
                            NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);
*/

// use this for "landscape mode"
const int WIDTH = 20;
const int HEIGHT = 16;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, DATA_PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS    + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

TextScroller* textScroller;
TextScroller* textScrollerSlow;
ScrollingChart* scrollingChart;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.show();
  matrix.setTextWrap(false);

  textScroller = new TextScroller(matrix, "Psssst...", 0, 20, matrix.Color(0,0,255));
  textScrollerSlow = new TextScroller(matrix, "Slow...", 9, 40, matrix.Color(0, 255, 0));
  scrollingChart = new ScrollingChart(matrix, 10, MAX_AMPLIFIER_VALUE);
}

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

void loop() {
   int noiseLevel = sampleSignal(SAMPLE_WINDOW_MS);

   // cut off permanent noise
   int level = map(max(noiseLevel - MIN_THRESHOLD, 0), 0, MAX_AMPLIFIER_VALUE - MIN_THRESHOLD, 0, MAX_AMPLIFIER_VALUE);
   scrollingChart->setValue(level);

  //bool requiresUpdate = textScroller->requiresUpdate() || textScrollerSlow->requiresUpdate();
  bool requiresUpdate = true;
  if(requiresUpdate) {
    matrix.fillScreen(0);
  }

  textScroller->next(requiresUpdate);
  //textScrollerSlow->next(requiresUpdate);
  scrollingChart->next(requiresUpdate);

  matrix.show();
}
