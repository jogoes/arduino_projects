#include "font8x8.h"

#include "data/font8x8.h"

Font8x8 Font8x8::font8x8;

char* 
Font8x8::charData(char c) {
    if(c < 0x20 || c > 0x7f) {
        return font8x8_basic[0];
    }
    return font8x8_basic[c - 0x20]; 
}

