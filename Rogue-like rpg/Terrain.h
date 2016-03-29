#pragma once

#include "Actor.h"
#include "Character.h"

class Terrain : public Actor
{
public:
	Terrain(Vec2i coords, char symb) :
		Actor(coords, symb)
		{
		}

	void collide(Map *map, Actor *target) { target->collide(map, this); }
	void collide(Map *map, Character *target) {}
};

class WoodBlock : public Terrain
{
public:
	WoodBlock(Vec2i coords, char symb) :
		Terrain(coords, symb)
	{
	}
};

class EmptyCell : public Terrain
{
public:
	EmptyCell(Vec2i coords, char symb) :
		Terrain(coords, symb)
	{
	}

	void collide(Map *map, Character *target);
};