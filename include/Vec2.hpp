#ifndef VEC2_HPP
#define VEC2_HPP
#include "SDL_include.h"
#include <math.h>

class Vec2{
private:

public:
    float x, y;
    Vec2();
    Vec2(float x, float y);

    Vec2 operator+ (Vec2 rhs);
    Vec2 operator- (Vec2 rhs);
    Vec2 operator* (float rhs);
    Vec2 operator+= (Vec2 rhs);
    Vec2 GetRotated(float angle);
    Vec2 Normalized();

    float Magnitude();
};

#endif