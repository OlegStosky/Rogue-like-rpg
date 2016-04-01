#include "Spawner.h"
#include <vector>

void Spawner::act(Map *map)
{
	if (isReady())
		spawn(map);
	_curCooldown++;
	map->setHasActed(_coords);
}

Vec2i Spawner::findEmptyCell(Map *map)
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			if (map->isValidCell(_coords + Vec2i(i, j)))
			{
				if (map->isEmptyCell(_coords + Vec2i(i, j)))
					return _coords + Vec2i(i, j);
			}
		}
	}

	return Vec2i(0, 0);
}

void Spawner::collide(Map *map, Magic *target)
{
	map->clearCell(target->coordinates());
}

void Graveyard::spawn(Map *map)
{
	Vec2i coords = findEmptyCell(map);
	if (coords == Vec2i(0, 0))
		return;
	Zombie *zombie = new Zombie(coords, ZOMBIE_HP, ZOMBIE_SYMB, ZOMBIE_DAMAGE);
	map->replace(coords, zombie);
	_curCooldown = 0;
}

void DragonNest::spawn(Map *map)
{
	Vec2i coords = findEmptyCell(map);
	if (coords == Vec2i(0, 0))
		return;
	Dragon *dragon = new Dragon(coords, ZOMBIE_HP, DRAGON_SYMB, DRAGON_DAMAGE);
	map->replace(coords, dragon);
	_curCooldown = 0;
}

void MedkitSpawner::act(Map *map)
{
	checkSpawned(map);
	_isRefreshing = false;
	if (_spawned.size() < 5)
		_isRefreshing = true;
	if (_isRefreshing)
		_curCooldown++;
	if (isReady())
		spawn(map);
}

void MedkitSpawner::checkSpawned(Map *map)
{
	std::vector<std::vector<Vec2i>::iterator> toBeDeleted;
	for (auto it = _spawned.begin(); it != _spawned.end(); ++it)
	{
		if (map->getActor(*it)->symbol() != MEDKIT_SYMB)
			toBeDeleted.push_back(it);
	}

	for (auto item : toBeDeleted)
		_spawned.erase(item);

}

void MedkitSpawner::spawn(Map *map)
{
		Vec2i pos = Vec2i(rand() % WIDTH, rand() % HEIGHT);
		if (map->isEmptyCell(pos))
		{
			Medkit *medkit = new Medkit(pos, MEDKIT_SYMB);
			map->replace(pos, medkit);
			_spawned.push_back(pos);
		}
		_curCooldown = 0;
}
