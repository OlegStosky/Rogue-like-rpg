#pragma once

#include <string>

using Direction = std::pair<int, int>;
using PairII = std::pair<int, int>;

const int INF = INT_MAX;
const int G_DISTANCE = 10;

const int WIDTH			= 12;
const int HEIGHT		= 2;

const int HERO_HP		= 100;
const int ZOMBIE_HP		= 30;
const int PRINCESS_HP	= 50;
const int DRAGON_HP = 40;

const int KNIGHT_DAMAGE	= 15;
const int ZOMBIE_DAMAGE = 10;
const int PRINCESS_DAMAGE = 10;
const int DRAGON_DAMAGE = 15;

const char PRINCESS_SYMB = 'P';
const char KNIGHT_SYMB = 'K';
const char ZOMBIE_SYMB = 'Z';
const char DRAGON_SYMB = 'D';
const char EMPTY_CELL_SYMB = '.';
const char WOOD_BLOCK_SYMB = '#';

const std::string PRINCESS_DEATH_MSG = "Princess is dead. You lost!";
const std::string HERO_DEATH_MSG = "Hero is dead";
const std::string NULL_ZOMBIE_MSG = "Coudn`t find zombie";
const std::string DELETE_ERR_MSG = "Trying to delete non existing monster";

const std::string INVALID_TILEMAP_ERR_MSG = "TileMap File is invalid";
const std::string NO_HERO_OR_PRINCESS_ERR_MSG = "Can`t start game without hero/princess";