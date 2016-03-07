#include "Game.h"
#include "Zombie.h"

using namespace std;

void Zombie::recieveDamage(int damage)
{
	_hp -= damage;

	ostringstream convert;
	convert << damage;
	Game::getInstance().pushLogMessage("Zombie recieved " + convert.str() + " damage.\n");
	convert.str("");
	convert.clear();
	convert << _hp;
	Game::getInstance().pushLogMessage("Zombie has " + convert.str() + " hp left.\n");

	if (_hp <= 0)
	{
		Game::getInstance().pushLogMessage("Zombie died.\n");
	}
}

Character* Zombie::findEnemy(Map *map)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (map->isValidCell(x() + i, y() + j))
			{
				if (map->isHero(x() + i, y() + j))
				{
					return Game::getInstance().getHero();
				}
				if (map->isPrincess(x() + i, y() + j))
				{
					return Game::getInstance().getPrincess();
				}
			}
		}
	}

	return nullptr;
}

void Zombie::move(Map *map)
{
	Character *enemy = findEnemy(map);

	if (enemy != nullptr)
	{
		try
		{
			enemy->recieveDamage(damage());
		}
		catch (exception &e)
		{
			if (e.what() == hero_death_message)
			{
				cout << e.what() << endl;
				Game::getInstance().setGameState("exiting");
			}
			if (e.what() == princess_death_message)
			{
				cout << e.what() << endl;
				Game::getInstance().setGameState("exiting");
			}

			cout << e.what();
		}

		return;
	}

	pair<int, int> move = map->getBestMove(x(), y());
	if (map->isValidCell(move.first, move.second))
	{
		if (map->isStone(move.first, move.second))
		{
			return;
		}

		if (map->isZombie(move.first, move.second))
		{
			return;
		}

		map->move(x(), y(), move.first, move.second);
		setX(move.first);
		setY(move.second);
	}
}