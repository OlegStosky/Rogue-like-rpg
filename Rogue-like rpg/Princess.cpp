#include "Game.h"
#include "Character.h"

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
