#include "Game.h"
#include "Princess.h"

Character* Princess::findMonster(Map *map) const
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (map->isValidCell(x() + i, y() + j))
			{
				if (map->isZombie(x() + i, y() + j))
				{
					return Game::getInstance().findMonster(x() + i, y() + j);
				}
			}
		}
	}

	return nullptr;
}

void Princess::move(Map *map)
{
	Character* monster = findMonster(map);
	if (monster == nullptr)
	{
		throw std::runtime_error(null_zombie_message);
	}
	monster->recieveDamage(damage());
	if (monster->isDead())
	{
		map->clearCell(monster->x(), monster->y());
	}
}