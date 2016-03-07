#pragma once

#include "Const.h"

class Point
{
public:
	Point(int h, int g, int f,
		int symb, int x, int y) :
		_h(h), _g(g), _f(f),
		_symb(symb), _y(y), _x(x),
		_parentX(x), _parentY(y){}

	Point(int x, int y, char symb) :
		_x(x), _y(y), _symb(symb),
		_h(0), _g(inf), _f(0) {}

	Point() : _h(0), _g(inf), _f(0),
		_symb(0), _x(0), _y(0),
		_parentX(0), _parentY(0){}

	inline int x(){ return _x; }
	inline int y(){ return _y; }
	inline int f(){ return _f; }
	inline char symb(){ return _symb; }

private:
	int _h, _g, _f; //a* metrics
	char _symb;
	int _x, _y;
	int _parentX, _parentY; //coordinates of the next cell, lying on the shortest path to hero

	friend class Map;
};
