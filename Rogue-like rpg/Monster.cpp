#include "Game.h"
#include "Character.h"

using namespace std;

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
}