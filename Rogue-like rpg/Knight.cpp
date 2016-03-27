#include "Game.h"
#include "Knight.h"

using namespace std;

Knight::Knight(int x, int y, int hp) : Character(x, y, hp)
{
}

void Knight::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("You recieved " + to_string(damage) + " damage\n");

	if (_hp <= 0)
	{
		throw std::runtime_error(hero_death_message);
	}
}

void Knight::setDirection(std::string dir)
{
	if (dir == "down")
	{
		_direction = Vec2i(0, 1);
		return;
	}
	if (dir == "up")
	{
		_direction = Vec2i(0, -1);
		return;
	}
	if (dir == "left")
	{
		_direction = Vec2i(-1, 0);
		return;
	}
	if (dir == "right")
	{
		_direction = Vec2i(1, 0);
		return;
	}
	
	_direction = Vec2i(0, 0); //default
}

void Knight::move(Map *map)
{
	string curMove;
	cin >> curMove;
	setDirection(curMove);
	
	if (newCoordinates() == _coordinates)
		return;

	if (map->isValidCell(newCoordinates()))
	{
		if (map->isPrincess(newCoordinates()))
		{
			cout << "You won!" << endl;
			Game::getInstance().setGameState("exiting");
		}

		if (map->isZombie(newCoordinates()))
		{
			Character *zombie = Game::getInstance().findMonster(newCoordinates());
			if (zombie == nullptr)
			{
				throw std::runtime_error(null_zombie_message);
			}

			zombie->recieveDamage(damage());
			if (zombie->isDead())
			{
				try
				{
					Game::getInstance().deleteMonster(zombie);
					map->clearCell(newCoordinates());
				}
				catch (exception &e)
				{
					cout << e.what() << endl;
					return;
				}
			}

			return;
		}

		if (map->isStone(newCoordinates()))
		{
			return;
		}

		map->move(_coordinates, newCoordinates());
		setCoordinates(newCoordinates());
	}
}

