#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "SDL_include.h"
#include "Rect.hpp"
#include "Vec2.hpp"

#include <algorithm>
#include <cmath>

class Collision {
	private:
		static inline float Mag(const Vec2& p);
		static inline Vec2 Norm(const Vec2& p);
		static inline float Dot(const Vec2& a, const Vec2& b);
		static inline Vec2 Rotate(const Vec2& p, float angle);
	public:
		static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
};

#endif