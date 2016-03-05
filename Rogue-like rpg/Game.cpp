#include "Game.h"

using namespace std;

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

Game::Game()
{
	_map = new Map;

	_map->readInp("map.txt");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			switch (_map->_map[i][j])
			{
			case 'H':
				_hero = new Knight(j, i, hero_hp);
				break;
			case 'Z':
				_monsters.push_back(new Zombie(j, i, zombie_hp));
				break;
			case 'P':
				_princess = new Princess(j, i, princess_hp);
				break;
			}
		}
	}

	_gameState = GameState::playing;
}

void Game::setGameState(string state)
{
	if (state == "playing")
		_gameState = GameState::playing;
	if (state == "paused")
		_gameState = GameState::paused;
	if (state == "exiting")
		_gameState = GameState::exiting;
}

void Game::start()
{
	while (!isExiting())
	{
		gameLoop();
	}
}

void Game::draw()
{
	_map->draw();
	cout << _hero->hitPoints() << endl;
	while (!_logMessages.empty())
	{
		cout << _logMessages.front();
		_logMessages.pop();
	}
}

void Game::gameLoop()
{
	draw();
	nextMove();
}

bool Game::isExiting()
{
	return (_gameState == GameState::exiting ? true : false);
}

void Game::nextMove()
{
	try
	{
		_hero->move(_map);
		_princess->move(_map);
	}
	catch (exception &e)
	{
		{
			cout << e.what();
			return;
		}
	}
	for (auto monster : _monsters)
	{
		try
		{
			monster->move(_map);
		}
		catch (exception &e)
		{
			cout << e.what();
			return;
		}
	}
}

Character* Game::findMonster(int x, int y)
{
	for (auto monster : _monsters)
	{
		if (monster->x() == x && monster->y() == y)
			return monster;
	}

	return nullptr;
}

void Game::deleteMonster(Character *target)
{
	auto it = find(_monsters.begin(), _monsters.end(), target);
	if (it == _monsters.end())
	{
		throw std::runtime_error(delete_error_message);
	}
	_monsters.erase(it);
}