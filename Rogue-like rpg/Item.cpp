#include "Item.h"
#include "Character.h"

void Medkit::collide(Map *map, Character *target)
{
	target->heal(MEDKIT_HEAL_POWER);
	map->clearCell(_coords);
}