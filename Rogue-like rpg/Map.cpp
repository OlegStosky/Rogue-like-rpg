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

void Map::move(int x, int y, int newX, int newY)
{
	if (isValidCell(x, y) && isValidCell(newX, newY))
	{
		_map[newY][newX]._symb = _map[y][x]._symb;
		_map[y][x]._symb = '.';
	}
}

void Map::clearCell(int x, int y)
{
	_map[y][x]._symb = '.';
}

void Map::init(int x, int y)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			_map[i][j]._h = abs(x - j) + abs(y - i);
			_map[i][j]._g = inf;
			_map[i][j]._f = 0;
		}
	}
}

void Map::traverse(Heap &heap, vector< pair<int, int> > &wasVisited, Point cur)
{
	int x = cur._x;
	int y = cur._y;
	wasVisited.push_back(make_pair(x, y));

	for (int i = -1; i <= 1; ++i)
	{
		if (i == 0)
			continue;
		/*if (isEndPoint(x + i, y))
		{
			if (!heap.empty())
			{
				Point nextPoint = heap.top();
				heap.pop();
				traverse(heap, wasVisited, nextPoint);
			}
			return;
		}*/
		if (isValidCell(x + i, y))
		{
			if (!isStone(x + i, y))
			{
				//if we havent traversed from this cell
				if (find(wasVisited.begin(), wasVisited.end(), (make_pair(x + i, y))) == wasVisited.end())
				{
					// If we can improve path to current cell
					if ((_map[y][x]._g + g_distance) < _map[y][x + i]._g)
					{
						_map[y][x + i]._parentX = x;
						_map[y][x + i]._parentY = y;
						_map[y][x + i]._g = _map[y][x]._g + g_distance;
						_map[y][x + i]._f = _map[y][x + i]._g + _map[y][x + i]._h;
						heap.push(_map[y][x + i]);
					}
				}
			}
		}
	}

	for (int i = -1; i <= 1; ++i)
	{
		if (i == 0)
			continue;
		if (isValidCell(x, y + i))
		{
			if (!isStone(x, y + i))
			{
				if (find(wasVisited.begin(), wasVisited.end(), (make_pair(x + i, y))) == wasVisited.end())
				{
					if ((_map[y][x]._g + g_distance) < _map[y + i][x]._g)
					{
						_map[y + i][x]._parentX = x;
						_map[y + i][x]._parentY = y;
						_map[y + i][x]._g = _map[y][x]._g + g_distance;
						_map[y + i][x]._f = _map[y + i][x]._g + _map[y + i][x]._h;
						heap.push(_map[y + i][x]);
					}
				}
			}
		}
	}

	if (!heap.empty())
	{
		Point nextPoint = heap.top();
		heap.pop();
		traverse(heap, wasVisited, nextPoint);
	}
}

//Calculates the shortest distances from all points to hero using a* algorithm
//Starting from x, y
void Map::calcShortestDistances(int x, int y)
{
	int heroX = Game::getInstance().getHero()->x();
	int heroY = Game::getInstance().getHero()->y();
	init(x, y);
	Heap heap;
	vector<pair<int, int>> wasVisited;
	_map[heroY][heroX]._g = 0; //cost of moving from starting point is zero
	traverse(heap, wasVisited, _map[heroY][heroX]);
}

pair<int, int> Map::getBestMove(int x, int y)
{
	return make_pair(_map[y][x]._parentX, _map[y][x]._parentY);
}

bool Map::isValidCell(int x, int y)
{
	return (x <= width - 1) && (x >= 0) && 
		(y <= height - 1) && (y >= 0);
}

bool Map::isPrincess(int x, int y)
{
	return _map[y][x]._symb == 'P';
}

bool Map::isStone(int x, int y)
{
	return _map[y][x]._symb == '#';
}

bool Map::isZombie(int x, int y)
{
	return _map[y][x]._symb == 'Z';
}

bool Map::isHero(int x, int y)
{
	return _map[y][x]._symb == 'H';
}

bool Map::isEndPoint(int x, int y)
{
	return x == end_point_x && y == end_point_y;
}