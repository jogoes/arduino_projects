#ifndef _TEXT_SCROLLER_H_
#define _TEXT_SCROLLER_H_

#include "animated.h"

/*
 * A simple text scroller implementation scrolling text from right to left in the specified matrix.
 */
class TextScroller : public Animated {

  private:
    Adafruit_NeoMatrix& m_matrix;
    const char* m_message;
    int m_width;
    int m_startPosition;
    int m_currentPosition;
    int m_row;
    int m_color;

  private:
    int getTextWidth() {
      int x1;
      int y1; 
      int w;
      int h;
      m_matrix.getTextBounds(m_message, 0, 0, &x1, &y1, &w, &h);
      return w;
    }

  public:
    TextScroller(Adafruit_NeoMatrix& matrix, const char* message, int row, int delayMs, int color) : Animated(delayMs), 
      m_matrix(matrix), m_message(message), m_row(row), m_color(color) {      
        m_width = getTextWidth();
        m_startPosition = m_matrix.width();
        m_currentPosition = m_startPosition;
    }

    const char* getMessage() const {
      return m_message;
    }

    virtual void onShow() {
      m_matrix.setCursor(m_currentPosition, m_row);
      m_matrix.setTextColor(m_color);
      m_matrix.print(getMessage());
    }
    
    virtual void onNext() {
      m_currentPosition--;
      if(m_currentPosition < -m_width) {
        m_currentPosition = m_startPosition;
      }
    }
};

#endif
