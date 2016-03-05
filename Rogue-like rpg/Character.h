#pragma once

#include "Map.h"

class Character
{
public:
	Character(int x, int y, int hp) : 
		_x(x),
		_y(y),
		_hp(hp)
		{
		}

	virtual char symbol() = 0 {};
	virtual void move(Map *map) {};
	inline int x() const { return _x; }
	void setX(int x){ _x = x; }
	void setY(int y){ _y = y; }
	inline int y() const { return _y; }
	inline int hitPoints() const { return _hp; }
	virtual int damage() const { return 10; };
	
	virtual void recieveDamage(int damage) {};

protected:
	int _x, _y;
	int _hp;
};