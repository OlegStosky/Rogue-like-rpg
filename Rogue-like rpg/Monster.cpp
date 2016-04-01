#include "Game.h"
#include "Character.h"
#include "Magic.h"

using namespace std;

void Monster::collide(Map *map, Knight *target)
{
	target->recieveDamage(_damage);
}

void Monster::collide(Map *map, Princess *target)
{
	target->recieveDamage(_damage);
}

void Monster::move(Map *map)
{
	Vec2i newCoords = map->calcShortestPath(map->getHero()->coordinates(), _coords);
	collide(map, map->getActor(newCoords));
	map->setHasActed(_coords);
}

void Dragon::move(Map *map)
{
	for (int i = -1; i < 1; ++i)
	{
		for (int j = -1; j < 1; ++j)
		{
			if (map->isHero(_coords + Vec2i(i, j)))
			{
				collide(map, map->getActor(_coords + Vec2i(i, j)));
				return;
			}
		}
	}
	_direction = Vec2i(rand() % 2, rand() % 2);
	if (map->isValidCell(newCoordinates()))
		collide(map, map->getActor(newCoordinates()));
	map->setHasActed(_coords);
}

void Zombie::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("Zombie received " + to_string(damage) + " damage.\n");
	Game::getInstance().pushLogMessage("Zombie has " + to_string(_hp) + " hp left.\n");

	if (isDead())
	{
		Game::getInstance().pushLogMessage("Zombie died.\n");
	}
}

void Zombie::heal(int ammount)
{
	_hp += ammount;
	if (_hp > ZOMBIE_HP)
		_hp = ZOMBIE_HP;
}

void Dragon::heal(int ammount)
{
	_hp += ammount;
	if (_hp > DRAGON_HP)
		_hp = DRAGON_HP;
}

void Dragon::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("Dragon received " + to_string(damage) + " damage.\n");
	Game::getInstance().pushLogMessage("Dragon has " + to_string(_hp) + " hp left.\n");

	if (isDead())
	{
		Game::getInstance().pushLogMessage("Dragon died.\n");
	}
}

Wizard::Wizard(Vec2i coords, int hp, char symb, int damage, int mana) :
	Monster(coords, hp, symb, damage),
	_mana(mana)
{
	_directions[0] = Vec2i(1, 0);
	_directions[1] = Vec2i(-1, 0);
	_directions[2] = Vec2i(0, 1);
	_directions[3] = Vec2i(0, -1);
}

void Wizard::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("Wizard received " + to_string(damage) + " damage.\n");
	Game::getInstance().pushLogMessage("Wizard has " + to_string(_hp) + " hp left.\n");

	if (isDead())
	{
		Game::getInstance().pushLogMessage("Wizard died.\n");
	}
}

void Wizard::heal(int ammount)
{
	_hp += ammount;
	if (_hp > WIZARD_HP)
		_hp = DRAGON_HP;
}

void Wizard::move(Map *map)
{
	_mana += WIZARD_MANA_REGEN;
	int curMove = rand() % 2;
	if (curMove == 0)
	{
		if (_mana >= FIREBALL_MANA_COST)
		{
			Vec2i fireBallDir = _directions[rand() % 4];
			Vec2i fireBallCoords = _coords + fireBallDir;
			if (map->isEmptyCell(fireBallCoords))
				map->replace(fireBallCoords, new FireBall(fireBallCoords, fireBallDir, FIREBALL_DAMAGE));
			_mana -= FIREBALL_MANA_COST;
		}
	}
	if (curMove == 1)
	{
		_direction = _directions[rand() % 4];
		if (map->isValidCell(newCoordinates()))
			collide(map, map->getActor(newCoordinates()));
	}
	map->setHasActed(_coords);
}