#ifndef _SCROLLING_CHART_H_
#define _SCROLLING_CHART_H_

#include "util/animated.h"
#include "display/display.h"

/*
 * A scrolling chart implementation showing a set of values as a moving set of bars.
 */
class ScrollingChart : public Animated {

  private:
      Display& m_display;
      // the array storing the current values for the scrollchart
      int* m_values;
      int m_maxValue;

  public:
    ScrollingChart(Display& display, int delayMs, int maxValue) : Animated(delayMs), m_display(display), m_maxValue(maxValue) {
      m_values = new int[display.width()];
      for(int i = 0; i < display.width(); i++) {
        m_values[i] = 0;
      }
    }

  private:
    void shiftLeft() {
      for(int i = 0; i < m_display.width() - 1; i++) {
        m_values[i] = m_values[i+1];
      }
    }

  public:
    void setValue(int value) {
      shiftLeft();
      m_values[m_display.width() - 1] = value;
    }

    void drawBar(int col, int value) {
      int height = m_display.height();
      int h = map(value, 0, m_maxValue, 0, height);
      if(h > 0) {
        for(int row = height - h; row < height; row++) {
          int t = map(row, 0, height - 1, 0, 255);
          // write individual pixels because each pixel has its own color
          m_display.writePixel(col, row, 255 - t, t, 0);
        }
      }
    }

  public:
    virtual void onShow() {
      int width = m_display.width();
      // draw bar for each column
      for(int col = 0; col < width; col++) {
        int value = m_values[col] < m_maxValue ? m_values[col] : m_maxValue;
        drawBar(col, value);
      }
    }

    virtual void onNext() { ; }
};
#endif
