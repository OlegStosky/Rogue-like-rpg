#include "Vec2i.h"

using namespace std;

double Vec2i::abs()
{
	return hypot(x, y);
}

Vec2i Vec2i::operator+(const Vec2i &rhs)
{
	return Vec2i(x + rhs.x, y + rhs.y);
}

Vec2i Vec2i::operator-(const Vec2i &rhs)
{
	return Vec2i(x - rhs.x, y - rhs.y);
}

Vec2i Vec2i::operator*(int rhs)
{
	return Vec2i(x * rhs, y * rhs);
}

Vec2i Vec2i::operator/(int rhs)
{
	return Vec2i(x / rhs, y / rhs);
}


bool Vec2i::operator==(const Vec2i &rhs)
{
	return x == rhs.x && y == rhs.y;
}

bool Vec2i::operator!=(const Vec2i &rhs)
{
	return x != rhs.x && y != rhs.y;
}