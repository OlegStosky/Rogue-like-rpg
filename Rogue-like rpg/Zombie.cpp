#include "Game.h"
#include "Zombie.h"

using namespace std;

void Zombie::move(Map *map)
{
	_dir.first = (rand() % 2) * pow(-1, rand() % 3);
	_dir.second = (rand() % 2) * pow(-1, rand() % 3);
	int newX = x() + _dir.first;
	int newY = y() + _dir.second;

	if (map->isValidCell(newX, newY))
	{
		if (map->isPrincess(newX, newY))
		{
			Game::getInstance().getPrincess()->recieveDamage(damage());
			if (Game::getInstance().getPrincess()->isDead())
			{
				throw std::runtime_error("Princess is dead. You lost!");
			}
		}

		if (map->isStone(newX, newY))
		{
			return;
		}

		if (map->isZombie(newX, newY))
		{
			return;
		}

		if (map->isHero(newX, newY))
		{
			Game::getInstance().getHero()->recieveDamage(damage());
			if (Game::getInstance().getHero()->isDead())
			{
				throw std::runtime_error("Hero is dead");
			}
		}

		map->move(x(), y(), newX, newY);
	}
}