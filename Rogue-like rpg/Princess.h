#pragma once

#include "Character.h"

class Princess : public Character
{
public:
	Princess(int x, int y, int hp) :
		Character(x, y, hp) {}

	char symbol() override { return 'P'; }
	void move(Map *map) override {};
	int damage() const override { return princess_damage; }
};