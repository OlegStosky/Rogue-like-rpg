#pragma once

#include "Vec2i.h"
#include "Map.h"

class Character;
class Terrain;
class Monster;
class Knight;
class Princess;
class Zombie;
class Dragon;
class Wizard;
class Item;
class Spawner;
class Magic;
class EmptyCell;
class WoodBlock;

class Actor
{
public:
	Actor(Vec2i coords, char symb) :
		_coords(coords),
		_symb(symb)
	{
	}
	virtual ~Actor(){}

	void setCoordinates(Vec2i coords) { _coords = coords; }
	char setSymbol(char symb) { _symb = symb; }
	Vec2i coordinates() { return _coords; }
	char symbol() { return _symb; }

	virtual void act(Map *map){}
	virtual void collide(Map *map, Actor *target) {}
	virtual void collide(Map *map, Character *target) {}
	virtual void collide(Map *map, Terrain *target) {}
	virtual void collide(Map *map, Item *target) {}
	virtual void collide(Map *map, Spawner *target) {}
	virtual void collide(Map *map, Magic *target) {}

protected:
	Vec2i _coords;
	char _symb;
};