#pragma once

#include "Character.h"
#include "Const.h"

class Princess : public Character
{
public:
	Princess(int x, int y, int hp) :
		Character(x, y, hp) {}

	char symbol() override { return 'P'; }
	int damage() const override { return princess_damage; }
	
	Character* findMonster(Map *map) const;
	void move(Map *map) override;
	void recieveDamage(int damage) override;
};