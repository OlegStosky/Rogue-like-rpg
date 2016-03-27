#include "Game.h"
#include "Zombie.h"

using namespace std;

void Zombie::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("Zombie recieved " + to_string(damage) + " damage.\n");
	Game::getInstance().pushLogMessage("Zombie has " + to_string(_hp) + " hp left.\n");

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
			_direction = Vec2i(i, j);
			if (map->isValidCell(newCoordinates()))
			{
				if (map->isHero(newCoordinates()))
				{
					return Game::getInstance().getHero();
				}
				if (map->isPrincess(newCoordinates()))
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

	Vec2i newCoordinates = map->calcShortestPath(Game::getInstance().getHero()->coordinates(), _coordinates);
	if (map->isValidCell(newCoordinates))
	{
		if (map->isStone(newCoordinates))
		{
			return;
		}

		if (map->isZombie(newCoordinates))
		{
			return;
		}

		map->move(_coordinates, newCoordinates);
		setCoordinates(newCoordinates);
	}
}