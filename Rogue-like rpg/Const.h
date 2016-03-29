#pragma once

#include <string>

using Direction = std::pair<int, int>;
using PairII = std::pair<int, int>;

const int inf = INT_MAX;
const int g_distance = 10;
const int end_point_x = 11;
const int end_point_y = 11;

const int width			= 12;
const int height		= 2;

const int hero_hp		= 100;
const int zombie_hp		= 30;
const int princess_hp	= 50;
const int dragon_hp = 40;

const int knight_damage	= 15;
const int zombie_damage = 10;
const int princess_damage = 10;
const int dragon_damage = 15;

const char princess_symb = 'P';
const char knight_symb = 'K';
const char zombie_symb = 'Z';
const char dragon_symb = 'D';
const char cell_symb = '.';
const char wood_block_symb = '#';

const std::string princess_death_message = "Princess is dead. You lost!";
const std::string hero_death_message = "Hero is dead";
const std::string null_zombie_message = "Coudn`t find zombie";
const std::string delete_error_message = "Trying to delete non existing monster";

const std::string invalid_tilemap_error_message = "TileMap File is invalid";
const std::string no_hero_or_princess_error_message = "Can`t start game without hero/princess";