#ifndef _DISPLAY_ADAFRUIT_NEOMATRIX_H_
#define _DISPLAY_ADAFRUIT_NEOMATRIX_H_

#include "display.h"

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


class Display_Adafruit_NeoMatrix : public Display {
private:
  Adafruit_NeoMatrix& m_matrix;

public:
  Display_Adafruit_NeoMatrix(Adafruit_NeoMatrix& matrix) : m_matrix(matrix) {
  }

  virtual int width() {
    return m_matrix.width();
  }

  virtual int height() {
    return m_matrix.height();
  }

  virtual void writePixel(int row, int col, int r, int g, int b) {
    m_matrix.writePixel(row, col, m_matrix.Color(r, g, b));
  }

  virtual void show() {
    m_matrix.show();
  }

  virtual void clear() {
    m_matrix.fillScreen(0);
  }
  
};

#endif
