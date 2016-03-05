#include "Map.h"

using namespace std;

void Map::readInp(std::string fileName)
{
	ifstream mapStream("map.txt");

	if (mapStream.is_open())
	{
		string inp;
		int curString = 0;
		while (getline(mapStream, inp))
		{
			for (int i = 0; i < width; ++i)
			{
				_map[curString][i] = inp[i];
			}
			curString++;
		}

		if (curString != width)
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
			cout << _map[i][j];
		}
		cout << endl;
	}
}

void Map::move(int y, int x, int newY, int newX)
{
	if (isValidCell(x, y) && isValidCell(newX, newY))
	{
		_map[newX][newY] = _map[x][y];
		_map[x][y] = '.';
	}
}

bool Map::isValidCell(int x, int y)
{
	return (x <= width) && (x >= 0) && 
		(y <= height) && (y >= 0);
}

bool Map::isPrincess(int x, int y)
{
	return _map[x][y] == 'P';
}

bool Map::isStone(int x, int y)
{
	return _map[x][y] == '#';
}

bool Map::isZombie(int x, int y)
{
	return _map[x][y] == 'Z';
}