#ifndef _TEXT_SCROLLER_H_
#define _TEXT_SCROLLER_H_

#include "fontrenderer.h"

#include "util/color.h"
#include "util/animated.h"

/*
 * A simple text scroller implementation scrolling text from right to left in the specified matrix.
 */
class TextScroller : public Animated {

  private:
    FontRenderer& m_fontRenderer;
    const char* m_message;
    int m_width;
    int m_startPosition;
    int m_currentPosition;
    int m_row;
    Color m_color;

  public:
    TextScroller(FontRenderer& fontRenderer, const char* message, int row, int delayMs, Color color) : Animated(delayMs),
      m_fontRenderer(fontRenderer), m_message(message), m_row(row), m_color(color) {
        m_width = m_fontRenderer.getWidth(message);
        m_startPosition = m_fontRenderer.getDisplay().width();
        m_currentPosition = m_startPosition;
    }

    const char* getMessage() const {
      return m_message;
    }

    virtual void onShow() {
      Color textColor = m_color;
      m_fontRenderer.putString(getMessage(), m_currentPosition, m_row, [textColor](const FontRendererContext& context, Color& color){ 
        if(context.foreground) {
          color = textColor; 
        } else {
          color = Color(0,0,0);
        }
      });
    }

    virtual void onNext() {
      m_currentPosition--;
      if(m_currentPosition < -m_width) {
        m_currentPosition = m_startPosition;
      }
    }
};

#endif
