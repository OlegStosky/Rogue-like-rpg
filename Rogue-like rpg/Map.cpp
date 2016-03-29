#include "Map.h"
#include "Game.h"
#include "Actor.h"
#include "Character.h"
#include "Terrain.h"

using namespace std;

void Map::init(std::string fileName)
{
	ifstream mapStream(fileName);

	if (mapStream.is_open())
	{
		string inp;
		int curString = 0;
		while (getline(mapStream, inp))
		{
			for (int i = 0; i < width; ++i)
			{
				switch (inp[i])
				{
				case knight_symb:
					_map[curString][i] = new Knight(Vec2i(i, curString), hero_hp, knight_symb, knight_damage);
					_hero = _map[curString][i];
					break;

				case princess_symb:
					_map[curString][i] = new Princess(Vec2i(i, curString), princess_hp, princess_symb, princess_damage);
					_princess = _map[curString][i];
					break;

				case zombie_symb:
					_map[curString][i] = new Zombie(Vec2i(i, curString), zombie_hp, zombie_symb, zombie_damage);
					break;

				case dragon_symb:
					_map[curString][i] = new Dragon(Vec2i(i, curString), dragon_hp, dragon_symb, dragon_damage);
					break;

				case cell_symb:
					_map[curString][i] = new EmptyCell(Vec2i(i, curString), cell_symb);
					break;

				case wood_block_symb:
					_map[curString][i] = new WoodBlock(Vec2i(i, curString), wood_block_symb);
					break;
				}
			}
			curString++;
		}

		if (curString != height)
		{
			throw runtime_error(invalid_tilemap_error_message);
		}

		if (_hero == nullptr || _princess == nullptr)
			throw runtime_error(no_hero_or_princess_error_message);
		
		mapStream.close();
	}
}

void Map::draw()
{
	system("cls");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cout << _map[i][j]->symbol();
		}
		cout << endl;
	}
}

void Map::move(Vec2i from, Vec2i to)
{
	if (isValidCell(from) && isValidCell(to))
	{
		swap(_map[from.y][from.x], _map[to.y][to.x]);
		_map[from.y][from.x]->setCoordinates(from);
		_map[to.y][to.x]->setCoordinates(to);
	}
}

Actor* Map::getActor(Vec2i actor)
{
	if (isValidCell(actor))
		return _map[actor.y][actor.x];
}

void Map::clearCell(Vec2i cell)
{
	delete _map[cell.y][cell.x];
	_map[cell.y][cell.x] = new EmptyCell(cell, cell_symb);
}

//Calculates shortest path between 2 points, using a* algorithm
Vec2i Map::calcShortestPath(Vec2i from, Vec2i to)
{
	Point info[height][width];
	init(to, info);
	Heap heap;
	vector<Vec2i> wasVisited;
	info[from.y][from.x].g = 0; //cost of moving from starting point is zero
	traverse(heap, wasVisited, info[from.y][from.x], to, info);
	return info[to.y][to.x].parent;
}

//init all the points for a*
void Map::init(Vec2i to, Point info[height][width])
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			info[i][j].coords = Vec2i(j, i);
			info[i][j].h = abs(to.x - j) + abs(to.y - i);
			info[i][j].g = inf;
			info[i][j].f = 0;
			info[i][j].symb = _map[i][j]->symbol();
		}
	}
}

void Map::traverse(Heap &heap, vector<Vec2i> &wasVisited, Point cur, Vec2i dest, Point info[height][width])
{
	if (cur.coords == dest)
		return;
	wasVisited.push_back(Vec2i(cur.coords));

	for (int i = 0; i < 4; ++i)
	{
		Vec2i curDir = Vec2i::getNextPair(i); // go through all neighbour cells
		Vec2i newCoord = cur.coords + curDir;
		if (isValidCell(newCoord))
		{
			if (isEmptyCell(newCoord) || (isZombie(newCoord) && newCoord == dest))
			{
				//if we havent traversed from this cell
				if (find(wasVisited.begin(), wasVisited.end(),
					newCoord) == wasVisited.end())
				{
					if ((info[cur.coords.y][cur.coords.x].g + g_distance) < info[newCoord.y][newCoord.x].g)
					{
						info[newCoord.y][newCoord.x].parent = cur.coords;
						info[newCoord.y][newCoord.x].g = info[cur.coords.y][cur.coords.x].g + g_distance;
						info[newCoord.y][newCoord.x].f = info[newCoord.y][newCoord.x].g +
							info[newCoord.y][newCoord.x].h;
						heap.push(info[newCoord.y][newCoord.x]);
					}
				}
			}
		}
	}

	if (!heap.empty())
	{
		Point nextPoint = heap.top();
		heap.pop();
		traverse(heap, wasVisited, nextPoint, dest, info);
	}
}

void Map::clearHasActed()
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			_hasActed[i][j] = false;
}

bool Map::isValidCell(Vec2i cell)
{
	return (cell.x <= width - 1) && (cell.x >= 0) && 
		(cell.y <= height - 1) && (cell.y >= 0);
}

bool Map::isEmptyCell(Vec2i cell)
{
	return _map[cell.y][cell.x]->symbol() == cell_symb	;
}

bool Map::isPrincess(Vec2i princess)
{
	return _map[princess.y][princess.x]->symbol() == princess_symb;
}

bool Map::isStone(Vec2i stone)
{
	return _map[stone.y][stone.x]->symbol() == wood_block_symb;
}

bool Map::isZombie(Vec2i zombie)
{
	return _map[zombie.y][zombie.x]->symbol() == zombie_symb;
}

bool Map::isHero(Vec2i hero)
{
	return _map[hero.y][hero.x]->symbol() == knight_symb;
}
