#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include "Map.h"
#include "Character.h"
#include "Knight.h"
#include "Zombie.h"
#include "Princess.h"

class Game
{
public:
	enum class GameState { playing, paused, exiting };

	static Game& getInstance();

	void setGameState(std::string state);
	inline Character* getHero(){ return _hero; }
	inline Character* getPrincess(){ return _princess; }
	
	void parseMap();
	void start();
	void printLog();
	void draw();
	void gameLoop();
	bool isExiting();

	void nextMove();
	void heroMove();
	inline void pushLogMessage(std::string message){ _logMessages.push(message); }

	Character* findMonster(Vec2i coordinates);
	void deleteMonster(Character *target);

	Game(const Game& rhs) = delete;
	Game& operator=(const Game &rhs) = delete;

private:
	Game();

	GameState _gameState;
	std::vector<Character*> _monsters;
	Knight *_hero;
	Princess *_princess;
	Map *_map;
	std::queue<std::string> _logMessages;
};