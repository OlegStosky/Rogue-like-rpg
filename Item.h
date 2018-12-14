#pragma once

#include "Actor.h"

class Item : public Actor
{
public:
	Item(Vec2i coords, char symb) : 
		Actor(coords, symb)
		{
		}

	void collide(Map *map, Character *target) override = 0;
	void collide(Map *map, Magic *target) override;
};

class Medkit : public Item
{
public:
	Medkit(Vec2i coords, char symb) : 
		Item(coords, symb) 
		{
		}

	void collide(Map *map, Character *target) override;
};