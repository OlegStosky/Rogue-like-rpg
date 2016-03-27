#pragma once

#include <vector>
#include <string> 
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <algorithm>
#include "Const.h"
#include "Point.h"
#include "Vec2i.h"

// Comparator for MinHeap 
struct PointCompare
{
	bool operator()(Point a, Point b) const { return a.f() > b.f(); }
};

using Heap = std::priority_queue<Point, std::vector<Point>, PointCompare>;

class Map
{
public:
	void readInp(std::string fileName);
	void draw();
	void move(Vec2i from, Vec2i to);
	void clearCell(Vec2i cell);
	
	void calcShortestDistances(Vec2i from);
	Vec2i getBestMove(Vec2i from);

	bool isValidCell(Vec2i cell);
	bool isPrincess(Vec2i princess);
	bool isZombie(Vec2i zombie);
	bool isStone(Vec2i stone);
	bool isHero(Vec2i hero);

private:
	Point _map[height][width];

	//a* methods
	void init(Vec2i from); 
	void traverse(Heap &heap,
		std::vector<Vec2i> &wasVisited,
		Point current);
	bool isEndPoint(Vec2i point);

	friend class Game;
};