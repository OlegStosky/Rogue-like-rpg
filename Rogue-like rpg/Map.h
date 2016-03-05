#pragma once

#include <vector>
#include <string> 
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Const.h"

using Direction = std::pair<int, int>;

class Map
{
public:
	void readInp(std::string fileName);
	void draw();
	bool isValidCell(int x, int y);
	bool isPrincess(int x, int y);
	bool isZombie(int x, int y);
	bool isStone(int x, int y);
	bool isHero(int x, int y);
	void move(int x, int y, int newX, int newY);

private:
	char _map[width][height];

	friend class Game;
};