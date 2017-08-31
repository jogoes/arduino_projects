#ifndef _FONT_RENDERER_H_
#define _FONT_RENDERER_H_

#include <functional>

class Display;
class Font;
class Color;

struct FontRendererContext {  
  bool foreground;
  int stringLength;
  char currentChar;
  int charStringPosition;  
  int charColumn;
  int charRow;
  int displayColumn;
  int displayRow;
};

using ColorMapper = std::function<void (const FontRendererContext&, Color&)>;

class FontRenderer {

public:
  private:
    Display& m_display;
    Font& m_font;

  public:
    FontRenderer(Display& display, Font& font) : m_display(display), m_font(font) {
    }

  private:
    void putChar(char c, int column, int row, FontRendererContext& context, ColorMapper colorMapper);

  public:
    Display& getDisplay() const { return m_display; }

  public:
    void putChar(char c, int column, int row);
    void putChar(char c, int column, int row, ColorMapper colorMapper);
    
    void putString(const char* str, int column, int row);
    void putString(const char* str, int column, int row, ColorMapper colorMapper);
    int getWidth(const char* str);
};

#endif
