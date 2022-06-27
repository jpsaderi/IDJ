#ifndef RECT_HPP
#define RECT_HPP

#include "SDL_include.h"
#include "Vec2.hpp"

class Rect{
private:

public:
    float x, y, w, h;
    Rect();
    Rect(float x, float y, float w, float h);
    Rect operator+(Vec2 rhs);
    
    bool Contains(Vec2 rhs);
};

#endif