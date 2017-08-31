#ifndef _FONT_8x8_H_
#define _FONT_8x8_H_

#include "font.h"

class Font8x8 : public Font {

private:
    static Font8x8 font8x8;

public:
    static Font& get() { return font8x8; }

public:
    virtual int charWidth() { return 8; }

    virtual int charHeight() { return 8; }

    virtual char* charData(char c);
};

#endif