#include "Item.h"
#include "Character.h"

void Medkit::collide(Map *map, Character *target)
{
	target->heal(MEDKIT_HEAL_POWER);
	map->clearCell(_coords);
	map->setHasActed(_coords);
}

void Item::collide(Map *map, Magic *target)
{
	map->clearCell(target->coordinates());
}