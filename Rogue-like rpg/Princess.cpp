#include "Game.h"
#include "Princess.h"

using namespace std;

void Princess::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("Princess recieved " + to_string(damage) + " damage\n");

	if (_hp <= 0)
	{
		throw std::runtime_error(princess_death_message);
	}
}

Character* Princess::findMonster(Map *map)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			_direction = Vec2i(i, j);
			if (map->isValidCell(newCoordinates()))
			{
				if (map->isZombie(newCoordinates()))
				{
					return Game::getInstance().findMonster(newCoordinates());
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
		Game::getInstance().deleteMonster(monster);
		map->clearCell(monster->coordinates());
	}
}