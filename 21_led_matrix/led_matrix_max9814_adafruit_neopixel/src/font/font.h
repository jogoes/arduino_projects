#ifndef _FONT_H_
#define _FONT_H_

class Font {

public:
    virtual int charWidth() = 0;
    virtual int charHeight() = 0;
    virtual char* charData(char c) = 0;
};

#endif