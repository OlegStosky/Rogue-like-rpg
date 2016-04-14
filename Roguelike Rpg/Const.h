#pragma once

#include <string>
#include <map>
#include "Vec2i.h"
#include "ConfigManager.h"

const int INF = INT_MAX;
const int G_DISTANCE = 10;

const int WIDTH = 27;
const int HEIGHT = 11;

const int KNIGHT_HP = ConfigManager::getInstance().getIntegerValue("KNIGHT_HP");
const int ZOMBIE_HP = ConfigManager::getInstance().getIntegerValue("ZOMBIE_HP");
const int PRINCESS_HP = ConfigManager::getInstance().getIntegerValue("PRINCESS_HP");
const int DRAGON_HP = ConfigManager::getInstance().getIntegerValue("DRAGON_HP");
const int WIZARD_HP = ConfigManager::getInstance().getIntegerValue("WIZARD_HP");
const int WIZARD_MANA = ConfigManager::getInstance().getIntegerValue("WIZARD_MANA");
const int WIZARD_MANA_REGEN = ConfigManager::getInstance().getIntegerValue("WIZARD_MANA_REGEN");

const int KNIGHT_DAMAGE = ConfigManager::getInstance().getIntegerValue("KNIGHT_DAMAGE");
const int ZOMBIE_DAMAGE = ConfigManager::getInstance().getIntegerValue("ZOMBIE_DAMAGE");
const int PRINCESS_DAMAGE = ConfigManager::getInstance().getIntegerValue("PRINCESS_DAMAGE");
const int DRAGON_DAMAGE = ConfigManager::getInstance().getIntegerValue("DRAGON_DAMAGE");
const int WIZARD_DAMAGE = ConfigManager::getInstance().getIntegerValue("WIZARD_DAMAGE");
const int FIREBALL_DAMAGE = ConfigManager::getInstance().getIntegerValue("FIREBALL_DAMAGE");
const int FIREBALL_MANA_COST = ConfigManager::getInstance().getIntegerValue("FIREBALL_MANA_COST");


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

const int GRAVEYARD_COOLDOWN = ConfigManager::getInstance().getIntegerValue("GRAVEYARD_COOLDOWN");
const int DRAGON_NEST_COOLDOWN = ConfigManager::getInstance().getIntegerValue("DRAGON_NEST_COOLDOWN");
const int MEDKIT_COOLDOWN = ConfigManager::getInstance().getIntegerValue("MEDKIT_COOLDOWN");

const int MEDKIT_HEAL_POWER = 10;

const std::string PRINCESS_DEATH_MSG = "Princess is dead. You lost!";
const std::string HERO_DEATH_MSG = "Hero is dead";
const std::string NULL_ZOMBIE_MSG = "Coudn`t find zombie";
const std::string DELETE_ERR_MSG = "Trying to delete non existing object";

const std::string INVALID_TILEMAP_ERR_MSG = "TileMap File is invalid";
const std::string NO_HERO_OR_PRINCESS_ERR_MSG = "Can`t start game without hero/princess";

const std::string FIREBAL_DIRECTION_ERR = "Unknown direction";

static std::map<int, Vec2i> DIRECTIONS = {
	{ 0, Vec2i(1, 0) },
	{ 1, Vec2i(-1, 0) },
	{ 2, Vec2i(0, 1) },
	{ 3, Vec2i(0, -1) }
};