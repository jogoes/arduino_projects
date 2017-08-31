#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class Display {
public:
  virtual int width() = 0;
  virtual int height() = 0;
  virtual void writePixel(int col, int row, int r, int g, int b) = 0;
  virtual void show() = 0;
  virtual void clear() = 0;
};

#endif
