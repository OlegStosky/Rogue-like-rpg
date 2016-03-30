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
			for (int i = 0; i < WIDTH; ++i)
			{
				switch (inp[i])
				{
				case KNIGHT_SYMB:
					_map[curString][i] = new Knight(Vec2i(i, curString), HERO_HP, KNIGHT_SYMB, KNIGHT_DAMAGE);
					_hero = _map[curString][i];
					break;

				case PRINCESS_SYMB:
					_map[curString][i] = new Princess(Vec2i(i, curString), PRINCESS_HP, PRINCESS_SYMB, PRINCESS_DAMAGE);
					_princess = _map[curString][i];
					break;

				case ZOMBIE_SYMB:
					_map[curString][i] = new Zombie(Vec2i(i, curString), ZOMBIE_HP, ZOMBIE_SYMB, ZOMBIE_DAMAGE);
					break;

				case DRAGON_SYMB:
					_map[curString][i] = new Dragon(Vec2i(i, curString), DRAGON_HP, DRAGON_SYMB, DRAGON_DAMAGE);
					break;

				case EMPTY_CELL_SYMB:
					_map[curString][i] = new EmptyCell(Vec2i(i, curString), EMPTY_CELL_SYMB);
					break;

				case WOOD_BLOCK_SYMB:
					_map[curString][i] = new WoodBlock(Vec2i(i, curString), WOOD_BLOCK_SYMB);
					break;
				}
			}
			curString++;
		}

		if (curString != HEIGHT)
		{
			throw runtime_error(INVALID_TILEMAP_ERR_MSG);
		}

		if (_hero == nullptr || _princess == nullptr)
			throw runtime_error(NO_HERO_OR_PRINCESS_ERR_MSG);
		
		mapStream.close();
	}
}

void Map::draw()
{
	system("cls");
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
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
	_map[cell.y][cell.x] = new EmptyCell(cell, EMPTY_CELL_SYMB);
}

//Calculates shortest path between 2 points, using a* algorithm
Vec2i Map::calcShortestPath(Vec2i from, Vec2i to)
{
	Point info[HEIGHT][WIDTH];
	init(to, info);
	Heap heap;
	vector<Vec2i> wasVisited;
	info[from.y][from.x].g = 0; //cost of moving from starting point is zero
	traverse(heap, wasVisited, info[from.y][from.x], to, info);
	return info[to.y][to.x].parent;
}

//init all the points for a*
void Map::init(Vec2i to, Point info[HEIGHT][WIDTH])
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			info[i][j].coords = Vec2i(j, i);
			info[i][j].h = abs(to.x - j) + abs(to.y - i);
			info[i][j].g = INF;
			info[i][j].f = 0;
			info[i][j].symb = _map[i][j]->symbol();
		}
	}
}

void Map::traverse(Heap &heap, vector<Vec2i> &wasVisited, Point cur, Vec2i dest, Point info[HEIGHT][WIDTH])
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
					if ((info[cur.coords.y][cur.coords.x].g + G_DISTANCE) < info[newCoord.y][newCoord.x].g)
					{
						info[newCoord.y][newCoord.x].parent = cur.coords;
						info[newCoord.y][newCoord.x].g = info[cur.coords.y][cur.coords.x].g + G_DISTANCE;
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
	for (int i = 0; i < HEIGHT; ++i)
		for (int j = 0; j < WIDTH; ++j)
			_hasActed[i][j] = false;
}

bool Map::isValidCell(Vec2i cell)
{
	return (cell.x <= WIDTH - 1) && (cell.x >= 0) && 
		(cell.y <= HEIGHT - 1) && (cell.y >= 0);
}

bool Map::isEmptyCell(Vec2i cell)
{
	return _map[cell.y][cell.x]->symbol() == EMPTY_CELL_SYMB	;
}

bool Map::isPrincess(Vec2i princess)
{
	return _map[princess.y][princess.x]->symbol() == PRINCESS_SYMB;
}

bool Map::isStone(Vec2i stone)
{
	return _map[stone.y][stone.x]->symbol() == WOOD_BLOCK_SYMB;
}

bool Map::isZombie(Vec2i zombie)
{
	return _map[zombie.y][zombie.x]->symbol() == ZOMBIE_SYMB;
}

bool Map::isHero(Vec2i hero)
{
	return _map[hero.y][hero.x]->symbol() == KNIGHT_SYMB;
}
