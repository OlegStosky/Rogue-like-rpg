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

			return;
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
			return;
		}

		map->move(x(), y(), newX, newY);
		setX(newX);
		setY(newY);
	}
}