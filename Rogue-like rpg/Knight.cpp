#include "Game.h"
#include "Knight.h"

using namespace std;

Knight::Knight(int x, int y, int hp) : Character(x, y, hp)
{
}

void Knight::recieveDamage(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		throw std::runtime_error(hero_death_message);
	}
}

void Knight::setDirection(std::string dir)
{
	if (dir == "down")
	{
		_dir = make_pair(0, 1);
	}
	if (dir == "up")
	{
		_dir = make_pair(0, -1);
	}
	if (dir == "left")
	{
		_dir = make_pair(-1, 0);
	}
	if (dir == "right")
	{
		_dir = make_pair(1, 0);
	}
}

void Knight::move(Map *map)
{
	string curMove;
	cin >> curMove;
	setDirection(curMove);
	
	int newX = x() + _dir.first;
	int newY = y() + _dir.second;
	if ((x() == newX) && (y() == newY))
		return;
	if (map->isValidCell(newX, newY))
	{
		if (map->isPrincess(newX, newY))
		{
			cout << "You won!" << endl;
			Game::getInstance().setGameState("exiting");
		}
		if (map->isZombie(newX, newY))
		{
			Character *zombie = Game::getInstance().findMonster(newX, newY);
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
					map->clearCell(newX, newY);
				}
				catch (exception &e)
				{
					cout << e.what() << endl;
					return;
				}
			}

			return;
		}
		if (map->isStone(newX, newY))
		{
			return;
		}

		map->move(x(), y(), newX, newY);
		setX(newX);
		setY(newY);
	}
}

