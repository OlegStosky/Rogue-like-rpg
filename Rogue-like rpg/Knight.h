#pragma once

#include <string>
#include <iostream>
#include <map>
#include "Character.h"
#include "Const.h"

class Knight : public Character
{
public:
	Knight(int x, int y, int hp);

	inline char symbol() { return 'k'; }
	inline int damage(){ return hero_damage; }
	const Direction& direction(){ return _dir; }

	void setDirection(std::string dir);
	void move(Map *map);
};