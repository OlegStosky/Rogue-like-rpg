#pragma once

#include <cmath>

struct Vec2i
{
	int x, y;

	Vec2i() : 
		x(0),
		y(0)
		{
		}
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
	bool operator==(const Vec2i &rhs);
	bool operator!=(const Vec2i &rhs);
};
