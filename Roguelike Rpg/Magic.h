#pragma once

#include "Actor.h"
#include "Vec2i.h"


class FireBall;

class Magic : public Actor
{
public:
	Magic(Vec2i coords, char symb, int power) :
		Actor(coords, symb),
		_power(power)
	{
	}

	void act(Map *map) override {};
	void collide(Map *map, Actor *target) override { target->collide(map, this); }
	void collide(Map *map, Character *target) override {};
	void collide(Map *map, Magic *target) override {}

protected:
	int _power;
};

class FireBall : public Magic
{
public:
	FireBall(Vec2i coords, Vec2i direction, int damage) :
		Magic(coords, getSymbolFromDir(direction), damage),
		_direction(direction)
		{
		}

	char getSymbolFromDir(Vec2i direction);
	void act(Map *map) override;
	void collide(Map *map, Actor *target) override { target->collide(map, this); }
	void collide(Map *map, Character *target) override;
	void collide(Map *map, Magic *target) override;
private:
	Vec2i _direction;
};