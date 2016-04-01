#pragma once

#include "Actor.h"
#include "Character.h"
#include "Magic.h"

class Terrain : public Actor
{
public:
	Terrain(Vec2i coords, char symb) :
		Actor(coords, symb)
		{
		}

	void collide(Map *map, Character *target){}
	void collide(Map *map, Magic *target){}
};

class WoodBlock : public Terrain
{
public:
	WoodBlock(Vec2i coords, char symb) :
		Terrain(coords, symb)
	{
	}

	void collide(Map *map, Magic *target);
};

class EmptyCell : public Terrain
{
public:
	EmptyCell(Vec2i coords, char symb) :
		Terrain(coords, symb)
	{
	}

	void collide(Map *map, Character *target);
	void collide(Map *map, Magic *target);
};