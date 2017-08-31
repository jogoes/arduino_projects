#ifndef _COLOR_H_
#define _COLOR_H_

class Color {

public:
    // TODO make these immutable
    int R;
    int G; 
    int B;

public:
    Color() : R(0), G(0), B(0) { }

    Color(int r, int g, int b) : R(r), G(g), B(b) { }

    Color(const Color& other) : R(other.R), G(other.G), B(other.B) { }

    Color& operator=(const Color& other) {
        this->R = other.R;
        this->G = other.G;
        this->B = other.B;
        return *this;
    }
};

#endif