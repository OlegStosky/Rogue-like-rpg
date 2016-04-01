#pragma once

#include <string>

using PairII = std::pair<int, int>;

const int INF = INT_MAX;
const int G_DISTANCE = 10;

const int WIDTH			= 27; //27
const int HEIGHT		= 11; //11

const int KNIGHT_HP		= 100;
const int ZOMBIE_HP		= 30;
const int PRINCESS_HP	= 50;
const int DRAGON_HP = 40;
const int WIZARD_HP = 30;
const int WIZARD_MANA = 30;
const int WIZARD_MANA_REGEN = 5;

const int KNIGHT_DAMAGE	= 15;
const int ZOMBIE_DAMAGE = 10;
const int PRINCESS_DAMAGE = 10;
const int DRAGON_DAMAGE = 15;
const int WIZARD_DAMAGE = 5;
const int FIREBALL_DAMAGE = 17;
const int FIREBALL_MANA_COST = 10;

const char PRINCESS_SYMB = 'P';
const char KNIGHT_SYMB = 'K';
const char ZOMBIE_SYMB = 'Z';
const char DRAGON_SYMB = 'D';
const char WIZARD_SYMB = 'W';
const char EMPTY_CELL_SYMB = '.';
const char WOOD_BLOCK_SYMB = '#';
const char GRAVEYARD_SYMB = 'G';
const char DRAGON_NEST_SYMB = 'N';
const char MEDKIT_SYMB = '+';

const int GRAVEYARD_COOLDOWN = 13;
const int DRAGON_NEST_COOLDOWN = 15;
const int MEDKIT_COOLDOWN = 3;

const int MEDKIT_HEAL_POWER = 10;

const std::string PRINCESS_DEATH_MSG = "Princess is dead. You lost!";
const std::string HERO_DEATH_MSG = "Hero is dead";
const std::string NULL_ZOMBIE_MSG = "Coudn`t find zombie";
const std::string DELETE_ERR_MSG = "Trying to delete non existing object";

const std::string INVALID_TILEMAP_ERR_MSG = "TileMap File is invalid";
const std::string NO_HERO_OR_PRINCESS_ERR_MSG = "Can`t start game without hero/princess";

const std::string FIREBAL_DIRECTION_ERR = "Unknown direction";