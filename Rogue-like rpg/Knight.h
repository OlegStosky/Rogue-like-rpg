#pragma once

#include <string>
#include <iostream>
#include <map>
#include "Character.h"
#include "Const.h"


using Direction = std::pair<int, int>;

class Knight : public Character
{
public:
	Knight(int x, int y, int hp);

	inline char symbol() { return 'k'; }
	inline int damage(){ return hero_damage; }
	const Direction& direction(){ return _dir; }

	void setDirection(std::string dir);
	
	void recieveDamage(int damage);

	void move(Map *map);

private:
	Direction _dir = std::make_pair(0, 0);
};