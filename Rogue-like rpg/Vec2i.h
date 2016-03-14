#pragma once

#include <cmath>

struct Vec2i
{
	int x, y;

	Vec2i(int x, int y) :
		x(x),
		y(y)
		{
		}
	
	double abs();
	Vec2i operator+(const Vec2i &rhs);
	Vec2i operator-(const Vec2i &rhs);
	Vec2i operator*(int rhs);
	Vec2i operator/(int rhs);
};