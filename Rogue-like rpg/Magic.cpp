#include "Magic.h"
#include "Character.h"
#include "Terrain.h"

void FireBall::act(Map *map)
{
	Vec2i coords = _coords;
	Vec2i newCoords = _coords + _direction;
	if (map->isValidCell(newCoords))
	{
		map->getActor(newCoords);
		collide(map, map->getActor(newCoords));
	}
	map->setHasActed(coords);
}

void FireBall::collide(Map *map, Character *target)
{
	target->recieveDamage(_power);
	if (target->isDead())
	{
		map->clearCell(target->coordinates());
	}
	map->clearCell(_coords);
}

char FireBall::getSymbolFromDir(Vec2i direction)
{
	if (direction == Vec2i(-1, 0))
		return '<';
	if (direction == Vec2i(1, 0))
		return '>';
	if (direction == Vec2i(0, -1))
		return '^';
	if (direction == Vec2i(0, 1))
		return 'v';

	throw std::runtime_error(FIREBAL_DIRECTION_ERR);
}

void FireBall::collide(Map *map, Magic *target)
{
	map->clearCell(target->coordinates());
	map->clearCell(_coords);
}
