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
				cout << princess_death_message;
				Game::getInstance().setGameState("exiting");
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
				cout << hero_death_message;
				Game::getInstance().setGameState("exiting");
			}
		}

		map->move(x(), y(), newX, newY);
	}
}