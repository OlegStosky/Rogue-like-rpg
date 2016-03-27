#pragma once

#include "Map.h"
#include "Const.h"
#include "Vec2i.h"

using Direction = std::pair < int, int > ;

class Character
{
public:
	Character(int x, int y, int hp) : 
		_coordinates(x, y),
		_hp(hp)
		{
		}
	virtual ~Character(){}

	virtual char symbol() const { return 'C'; }
	inline int hitPoints() const { return _hp; }
	virtual int damage() const { return 10; };
	inline Vec2i direction() const { return _direction; }
	inline Vec2i coordinates() const { return _coordinates; }
	inline Vec2i newCoordinates() const { return Vec2i(_coordinates) + Vec2i(_direction); }

	void setX(int x){ _coordinates.x = x; }
	void setY(int y){ _coordinates.y = y; }
	void setCoordinates(Vec2i coordinates){ _coordinates = coordinates; }
	
	virtual void recieveDamage(int damage) { _hp -= damage; }
	virtual void move(Map *map) {};
	
	inline bool isDead(){ return (_hp <= 0 ? true : false); }

protected:
	Vec2i _coordinates;
	Vec2i _direction;
	int _hp;
};