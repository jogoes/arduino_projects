#ifndef _FAST_LED_H_
#define _FAST_LED_H_

#include "display.h"

#include <FastLED.h>

struct CRGB;

template <uint8_t DATA_PIN> class Display_FastLED : public Display {

private:
  int m_rows;
  int m_cols;
  CRGB* m_leds;

public:
  Display_FastLED(int rows, int cols) : m_rows(rows), m_cols(cols) {
    m_leds = new CRGB[rows * cols];
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(m_leds, rows*cols);
  }

  virtual ~Display_FastLED() {
    delete[] m_leds;
  }

private:
  void setLED(int n, int r, int g, int b) {
    m_leds[n].setRGB(r, g, b);
  }

  void setLED(int n, const CRGB& color) {
    m_leds[n] = color;
  }

public:
  virtual int width() { return m_cols; }
  virtual int height() { return m_rows; }

  virtual void writePixel(int col, int row, int r, int g, int b) {
    if(col < 0 || col >= width()) {
      return;
    }
    if(row < 0 || row >= height()) {
      return;
    }

    int offset;
    if(row % 2 == 0) {
      offset = (width() - 1) - col;
    } else {
      offset = col;
    }
    int index = row * width() + offset;
    if(index >= height() * width()) {
      return;
    }
    setLED(index, r, g, b);
  }

  virtual void show() {
    FastLED.show();
  }

  virtual void clear() {
    for(int i = 0; i < width() * height(); i++) {
      m_leds[i] = CRGB(0, 0, 0);
    }
  }
};
#endif
