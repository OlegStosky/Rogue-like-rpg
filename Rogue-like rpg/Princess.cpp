#include "Game.h"
#include "Princess.h"

void Princess::recieveDamage(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		throw std::runtime_error(princess_death_message);
	}
}

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
		return;
	}
	monster->recieveDamage(damage());
	if (monster->isDead())
	{
		map->clearCell(monster->x(), monster->y());
	}
}