#include "Terrain.h"

void EmptyCell::collide(Map *map, Character *target)
{
	map->move(target->coordinates(), coordinates());
	map->setHasActed(target->coordinates());
	map->setHasActed(_coords);
}

void EmptyCell::collide(Map *map, Magic *target)
{
	map->move(target->coordinates(), coordinates());
	map->setHasActed(target->coordinates());
	map->setHasActed(_coords);
}

void WoodBlock::collide(Map* map, Magic *target)
{
	map->clearCell(target->coordinates());
}