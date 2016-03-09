#pragma once

#include "Map.h"
#include "Const.h"

using Direction = std::pair < int, int > ;

class Character
{
public:
	Character(int x, int y, int hp) : 
		_x(x),
		_y(y),
		_hp(hp)
		{
		}

	virtual char symbol() const = 0 {};
	inline int hitPoints() const { return _hp; }
	virtual int damage() const { return 10; };
	inline int x() const { return _x; }
	inline int y() const { return _y; }

	void setX(int x){ _x = x; }
	void setY(int y){ _y = y; }
	
	virtual void recieveDamage(int damage) { _hp -= damage; }
	virtual void move(Map *map) {};
	
	inline bool isDead(){ return (_hp <= 0 ? true : false); }

protected:
	int _x, _y;
	int _hp;
	Direction _dir = std::make_pair(0, 0);
};