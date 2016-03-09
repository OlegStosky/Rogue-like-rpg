#pragma once

#include "Game.h"
#include "Map.h"
#include "Character.h"
#include "Const.h"


class Dragon : public Character
{
public:
	inline char symbol() const override { return 'D'; }
	int damage() const  override { return dragon_damage; }
	
	void recieveDamage(int damage) override;
	void move(Map *map) override;
};