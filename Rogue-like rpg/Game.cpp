#include "Game.h"
#include "Spawner.h"

using namespace std;

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

Game::Game()
{
	_map = new Map;

	try
	{
		_map->init("map.txt");
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
		return;
	}

	setGameState(GameState::playing);
}

void Game::start()
{
	while (!isExiting())
	{
		gameLoop();
	}
}

void Game::gameLoop()
{
	draw();
	nextMove();
}

void Game::nextMove()
{
	_map->clearHasActed();
	_map->getHero()->act(_map);
	_map->getPrincess()->act(_map);
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (!_map->hasActed(Vec2i(j, i)))
				_map->getActor(Vec2i(j, i))->act(_map);
		}
	}
	vector<RemoteSpawner*> spawners = _map->getSpawners();
	for (auto spawner : spawners)
		spawner->act(_map);
}


void Game::draw()
{
	_map->draw();
	cout << "Your hp : " << _map->getHero()->hitPoints() << endl;
	cout << "Princess hp : " << _map->getPrincess()->hitPoints() << endl;
	printLog();
}

void Game::printLog()
{
	while (!_logMessages.empty())
	{
		cout << _logMessages.front();
		_logMessages.pop();
	}
}

void Game::setGameState(GameState state)
{
	_gameState = state;
}

bool Game::isExiting()
{
	return (_gameState == GameState::exiting ? true : false);
}