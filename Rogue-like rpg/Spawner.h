#pragma once

#include <vector>
#include "Map.h"
#include "Spawnable.h"
#include "Actor.h"
#include "Vec2i.h"
#include "Character.h"
#include "Const.h"
#include "Item.h"

class Spawner : public Actor
{
public:
	Spawner(Vec2i coords, char symbol, int cooldown) : 
		Actor(coords, symbol),
		_cooldown(cooldown),
		_curCooldown(0)
		{
		}

	void act(Map *map) override;
	virtual void spawn(Map *map) = 0;
	bool isReady() { return _curCooldown >= _cooldown; }
	void collide(Map *map, Magic *target) override;


protected:
	int _cooldown;
	int _curCooldown;

	Vec2i findEmptyCell(Map *map);
};

class Graveyard : public Spawner
{
public:
	Graveyard(Vec2i coords, char symbol, int cooldown) :
		Spawner(coords, symbol, cooldown)
	{
	}

	void spawn(Map *map) override;
};

class DragonNest : public Spawner
{
public:
	DragonNest(Vec2i coords, char symbol, int cooldown) :
		Spawner(coords, symbol, cooldown)
	{
	}

	void spawn(Map *map) override;
};

class RemoteSpawner
{
public:
	RemoteSpawner(int cooldown) :
		_cooldown(cooldown),
		_curCooldown(0)
		{
		}
	virtual ~RemoteSpawner() {}

	virtual void act(Map *map) = 0;
	bool isReady(){ return _curCooldown >= _cooldown; }

protected:
	int _cooldown;
	int _curCooldown;
	std::vector<Vec2i> _spawned;

	void spawn(Map *map);
	void checkSpawned(Map *map);

};

class MedkitSpawner : public RemoteSpawner
{
public:
	MedkitSpawner(int cooldown) : 
		RemoteSpawner(cooldown),
		_isRefreshing(0)
		{
		}

	void act(Map *map) override;

protected:
	bool _isRefreshing;

	void spawn(Map *map);
	void checkSpawned(Map *map);
};