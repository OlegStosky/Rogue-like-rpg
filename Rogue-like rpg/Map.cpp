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



//Calculates the shortest distances from all points to hero using a* algorithm
//Starting from x, y
void Map::calcShortestDistances(int x, int y)
{
	int heroX = Game::getInstance().getHero()->x();
	int heroY = Game::getInstance().getHero()->y();
	init(x, y);
	Heap heap;
	vector<PairII> wasVisited;
	_map[heroY][heroX]._g = 0; //cost of moving from starting point is zero
	traverse(heap, wasVisited, _map[heroY][heroX]);
}

//init all the points for a*
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

//helper function for going through neighbor cells
PairII getNextPair(int cnt)
{

	if (cnt < 2)
	{
		return make_pair(pow(-1, cnt), 0); //this will return (-1, 0), (1, 0)
	}
	else
	{
		return make_pair(0, pow(-1, cnt % 2)); //this will return (0, -1), (0, 1)
	}
}

void Map::traverse(Heap &heap, vector<PairII> &wasVisited, Point current)
{
	int x = current._x;
	int y = current._y;
	wasVisited.push_back(make_pair(x, y));

	for (int i = 0; i < 4; ++i)
	{
		PairII cur = getNextPair(i); // go through all neighbour cells
		if (isValidCell(x + cur.first, y + cur.second))
		{
			if (!isStone(x + cur.first, y + cur.second))
			{
				//if we havent traversed from this cell
				if (find(wasVisited.begin(), wasVisited.end(),
					(make_pair(x + cur.first, y + cur.second))) == wasVisited.end())
				{
					if ((_map[y][x]._g + g_distance) < _map[y + cur.second][x + cur.first]._g)
					{
						_map[y + cur.second][x + cur.first]._parentX = x;
						_map[y + cur.second][x + cur.first]._parentY = y;
						_map[y + cur.second][x + cur.first]._g = _map[y][x]._g + g_distance;
						_map[y + cur.second][x + cur.first]._f = _map[y + cur.second][x + cur.first]._g +
							_map[y + cur.second][x + cur.first]._h;
						heap.push(_map[y + cur.second][x + cur.first]);
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

PairII Map::getBestMove(int x, int y)
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