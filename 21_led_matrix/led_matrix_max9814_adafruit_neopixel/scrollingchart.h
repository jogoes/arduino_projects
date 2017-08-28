#ifndef _SCROLLING_CHART_H_
#define _SCROLLING_CHART_H_

#include "animated.h"

/*
 * A scrolling chart implementation showing a set of values as a moving set of bars.
 */
class ScrollingChart : public Animated {

  private:
      Adafruit_NeoMatrix& m_matrix;
      // the array storing the current values for the scrollchart
      int* m_values;
      int m_maxValue;

  public:
    ScrollingChart(Adafruit_NeoMatrix& matrix, int delayMs, int maxValue) : Animated(delayMs), m_matrix(matrix), m_maxValue(maxValue) {
      m_values = new int[m_matrix.width()];
      for(int i = 0; i < m_matrix.width(); i++) {
        m_values[i] = 0;
      }
    }

  private:    
    void shiftLeft() {
      for(int i = 0; i < m_matrix.width() - 1; i++) {
        m_values[i] = m_values[i+1];        
      }
    }
    
  public:
    void setValue(int value) {
      shiftLeft();
      m_values[m_matrix.width() - 1] = value;
    }

    void drawBar(int col, int value) {
      int height = m_matrix.height();
      int h = map(value, 0, m_maxValue, 0, height);
      if(h > 0) {
        for(int row = height - h; row < height; row++) {
          int t = map(row, 0, height - 1, 0, 255);
          // write individual pixels because each pixel has its own color
          m_matrix.writePixel(col, row, m_matrix.Color(255 - t, t, 0));
        }
      }
    }

  public:
    virtual void onShow() {
      int width = m_matrix.width();
      // draw bar for each column
      for(int col = 0; col < width; col++) {
        int value = min(m_values[col], m_maxValue); 
        drawBar(col, value);
      }
    }

    virtual void onNext() { ; }    
};
#endif
