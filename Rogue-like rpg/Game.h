#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include "Map.h"
#include "Character.h"

class Game
{
public:
	enum class GameState { playing, paused, exiting };

	static Game& getInstance();
	~Game();

	void start();
	void gameLoop();
	void nextMove();
	void draw();
	void setGameState(GameState state);
	void printLog();
	bool isExiting();
	inline void pushLogMessage(std::string message){ _logMessages.push(message); }

	Game(const Game& rhs) = delete;
	Game& operator=(const Game &rhs) = delete;

private:
	Game();

	GameState _gameState;
	Map *_map;
	std::queue<std::string> _logMessages;
};