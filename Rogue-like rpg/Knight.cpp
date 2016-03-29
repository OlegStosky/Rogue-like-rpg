#include <conio.h>
#include "Game.h"
#include "Character.h"


using namespace std;

Knight::Knight(Vec2i coords, int hp, char symb, int damage) : Character(coords, hp, symb, damage)
{
	_directions['s'] = Vec2i(0, 1);
	_directions['w'] = Vec2i(0, -1);
	_directions['a'] = Vec2i(-1, 0);
	_directions['d'] = Vec2i(1, 0);
}

void Knight::recieveDamage(int damage)
{
	_hp -= damage;

	Game::getInstance().pushLogMessage("You received " + to_string(damage) + " damage\n");
	if (isDead())
		Game::getInstance().setGameState(Game::GameState::exiting);
}

void Knight::setDirection(char dir)
{
	auto it = _directions.find(dir);
	if (it != _directions.end())
		_direction = it->second;
	else
		_direction = Vec2i(0, 0); //default
}

void Knight::collide(Map *map, Monster *target)
{
	target->recieveDamage(_damage);
	if (target->isDead())
		map->clearCell(target->coordinates());
}

void Knight::collide(Map *map, Princess *target)
{
	Game::getInstance().setGameState(Game::GameState::exiting);
}

void Knight::move(Map *map)
{
	char dir = _getch();
	setDirection(dir);
	if (map->isValidCell(newCoordinates()))
		collide(map, map->getActor(newCoordinates()));
	map->setHasActed(_coords);
}