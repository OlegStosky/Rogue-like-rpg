#include "Map.h"
#include "Game.h"

using namespace std;

void Map::readInp(std::string fileName)
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
				_map[curString][i] = Point(i, curString, inp[i]);
			}
			curString++;
		}

	 	if (curString != height)
		{
			throw runtime_error("TileMap File is invalid");
		} 
		
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
			cout << _map[i][j].symb();
		}
		cout << endl;
	}
}

void Map::move(Vec2i from, Vec2i to)
{
	if (isValidCell(from) && isValidCell(to))
	{
		char tmp = _map[from.y][from.x].symb();
		_map[from.y][from.x]._symb = _map[to.y][to.x]._symb;
		_map[to.y][to.x]._symb = tmp;
	}
}

void Map::clearCell(Vec2i cell)
{
	_map[cell.y][cell.x]._symb = '.';
}

//Calculates shortest path between 2 points, using a* algorithm
Vec2i Map::calcShortestPath(Vec2i from, Vec2i to)
{
	init(to);
	Heap heap;
	vector<Vec2i> wasVisited;
	_map[from.y][from.x]._g = 0; //cost of moving from starting point is zero
	traverse(heap, wasVisited, _map[from.y][from.x], to);
	return Vec2i(_map[to.y][to.x]._parentX, _map[to.y][to.x]._parentY);
}

//init all the points for a*
void Map::init(Vec2i from)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			_map[i][j]._h = abs(from.x - j) + abs(from.y - i);
			_map[i][j]._g = inf;
			_map[i][j]._f = 0;
		}
	}
}

//helper function for going through neighbor cells
Vec2i getNextPair(int cnt)
{

	if (cnt < 2)
	{
		return Vec2i(pow(-1, cnt), 0); //this will return (-1, 0), (1, 0)
	}
	else
	{
		return Vec2i(0, pow(-1, cnt % 2)); //this will return (0, -1), (0, 1)
	}
}

void Map::traverse(Heap &heap, vector<Vec2i> &wasVisited, Point current, Vec2i dest)
{
	Vec2i curPoint = Vec2i(current.x(), current.y());
	if (curPoint == dest)
		return;
	wasVisited.push_back(Vec2i(curPoint.x, curPoint.y));

	for (int i = 0; i < 4; ++i)
	{
		Vec2i curDir = getNextPair(i); // go through all neighbour cells
		Vec2i newCoord = curPoint + curDir;
		if (isValidCell(newCoord))
		{
			if (isEmptyCell(newCoord) || (isZombie(newCoord) && newCoord == dest))
			{
				//if we havent traversed from this cell
				if (find(wasVisited.begin(), wasVisited.end(),
					newCoord) == wasVisited.end())
				{
					if ((_map[curPoint.y][curPoint.x]._g + g_distance) < _map[newCoord.y][newCoord.x]._g)
					{
						_map[newCoord.y][newCoord.x]._parentX = curPoint.x;
						_map[newCoord.y][newCoord.x]._parentY = curPoint.y;
						_map[newCoord.y][newCoord.x]._g = _map[curPoint.y][curPoint.x]._g + g_distance;
						_map[newCoord.y][newCoord.x]._f = _map[newCoord.y][newCoord.x]._g +
							_map[newCoord.y][newCoord.x]._h;
						heap.push(_map[newCoord.y][newCoord.x]);
					}
				}
			}
		}
	}

	if (!heap.empty())
	{
		Point nextPoint = heap.top();
		heap.pop();
		traverse(heap, wasVisited, nextPoint, dest);
	}
}

bool Map::isValidCell(Vec2i cell)
{
	return (cell.x <= width - 1) && (cell.x >= 0) && 
		(cell.y <= height - 1) && (cell.y >= 0);
}

bool Map::isEmptyCell(Vec2i cell)
{
	return _map[cell.y][cell.x].symb() == '.';
}

bool Map::isPrincess(Vec2i princess)
{
	return _map[princess.y][princess.x]._symb == 'P';
}

bool Map::isStone(Vec2i stone)
{
	return _map[stone.y][stone.x]._symb == '#';
}

bool Map::isZombie(Vec2i zombie)
{
	return _map[zombie.y][zombie.x]._symb == 'Z';
}

bool Map::isHero(Vec2i hero)
{
	return _map[hero.y][hero.x]._symb == 'H';
}
