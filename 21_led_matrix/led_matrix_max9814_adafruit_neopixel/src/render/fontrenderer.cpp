
#include <Arduino.h>

#include "fontrenderer.h"
#include "display/display.h"

#include "font/font.h"

#include "util/color.h"

#include <functional>

int
FontRenderer::getWidth(const char* str) {
  if(str == NULL) {
    return 0;
  }

  auto strLength = strlen(str);
  return strLength * m_font.charWidth();
}

void
FontRenderer::putChar(char c, int column, int row) {
  putChar(c, column, row, [](const FontRendererContext& context, Color& color) { color = context.foreground ? Color(255, 255, 255) : Color(0, 0, 0); });
}

void
FontRenderer::putChar(char c, int displayColumn, int displayRow, ColorMapper colorMapper) {
  FontRendererContext context;
  context.stringLength = 1;
  context.currentChar = c;
  context.charStringPosition = 0;    
  putChar(c, displayColumn, displayRow, context, colorMapper); 
}

void
FontRenderer::putChar(char c, int displayColumn, int displayRow, FontRendererContext& context, ColorMapper colorMapper) {
  char* charData = m_font.charData(c);

  context.currentChar = c;

  Color color;
  for(int row = 0; row < m_font.charHeight(); row++) {
    char rowData = charData[row];
    char mask = 1;
    context.charRow = row;
    context.displayRow = displayRow + row;
    for(int col = 0; col < m_font.charWidth(); col++) {
      bool foreground = rowData & mask;
      context.foreground = foreground;
      context.charColumn = col;
      context.displayColumn = displayColumn + col;
      colorMapper(context, color);      
      m_display.writePixel(context.displayColumn, context.displayRow, color.R, color.G, color.B);
      mask = mask << 1;
    }
  }
}

void
FontRenderer::putString(const char* str, int column, int row) {
  for(int l = 0; l < strlen(str); l++) {
    int col = l * 8;
    putChar(str[l], column + col, row);
  }
}

void
FontRenderer::putString(const char* str, int column, int row, ColorMapper colorMapper) {
  int strLength = strlen(str);
  FontRendererContext context;
  context.stringLength = strLength;
  for(int l = 0; l < strLength; l++) {
    int col = l * m_font.charWidth();
    char c = str[l];
    context.currentChar = c;
    context.charStringPosition = l;    
    putChar(c, column + col, row, context, colorMapper); 
  }
}
