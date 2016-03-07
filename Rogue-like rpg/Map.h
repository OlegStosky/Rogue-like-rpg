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
	void move(int x, int y, int newX, int newY);
	void clearCell(int x, int y);
	
	void calcShortestDistances(int x, int y);
	std::pair<int,int> getBestMove(int x, int y);

	bool isValidCell(int x, int y);
	bool isPrincess(int x, int y);
	bool isZombie(int x, int y);
	bool isStone(int x, int y);
	bool isHero(int x, int y);

private:
	Point _map[height][width];

	//a* methods
	void init(int x, int y); 
	void traverse(Heap &heap,
		std::vector<PairII> &wasVisited,
		Point current);
	bool isEndPoint(int x, int y);

	friend class Game;
};