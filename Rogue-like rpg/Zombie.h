#pragma once

#include <cmath>
#include <sstream>
#include "Character.h"
#include "Const.h"

class Zombie : public Character
{
public:
	Zombie(int x, int y, int hp) :
		Character(x, y, hp) {}

	inline char symbol() override { return 'z'; }
	inline int damage() const override { return zombie_damage; }

	void recieveDamage(int damage) override;
	Character* findEnemy(Map *map);
	void move(Map *map) override;
};
