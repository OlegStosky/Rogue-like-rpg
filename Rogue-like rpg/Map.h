#pragma once

#include <vector>
#include <string> 
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <queue>
#include <algorithm>
#include "Const.h"
#include "Vec2i.h"

class Actor;
class Character;

class Map
{
public:
	void init(std::string fileName);
	void draw();
	void move(Vec2i from, Vec2i to);
	Vec2i calcShortestPath(Vec2i from, Vec2i to);
	void clearHasActed();
	void clearCell(Vec2i cell);
	bool hasActed(Vec2i coords){ return _hasActed[coords.y][coords.x]; }
	void setHasActed(Vec2i coords){ _hasActed[coords.y][coords.x] = true; }

	Actor* getActor(Vec2i character);
	Character* getHero(){ return (Character*)_hero; }
	Character* getPrincess(){ return (Character*)_princess; }

	bool isValidCell(Vec2i cell);
	bool isEmptyCell(Vec2i cell);
	bool isPrincess(Vec2i princess);
	bool isZombie(Vec2i zombie);
	bool isStone(Vec2i stone);
	bool isHero(Vec2i hero);

private:
	Actor* _map[HEIGHT][WIDTH];
	Actor *_hero;
	Actor *_princess;
	bool _hasActed[HEIGHT][WIDTH];

	class Point
	{
	public:
		int h, g, f; //a* metrics
		char symb;
		Vec2i coords;
		Vec2i parent; //coordinates of the next cell, lying on the shortest path to hero
	};

	// Comparator for MinHeap 
	struct PointCompare
	{
		bool operator()(Point a, Point b) const { return a.f > b.f; }
	};

	using Heap = std::priority_queue<Point, std::vector<Point>, PointCompare>;

	//a* methods
	void init(Vec2i to, Point info[HEIGHT][WIDTH]); 
	void traverse(Heap &heap,
		std::vector<Vec2i> &wasVisited,
		Point cur, Vec2i dest, Point info[HEIGHT][WIDTH]);

	friend class Game;
};