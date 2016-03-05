#pragma once

#include <string>

const int width			= 10;
const int height		= 10;

const int hero_hp		= 100;
const int zombie_hp		= 30;
const int princess_hp	= 50;

const int hero_damage	= 15;
const int zombie_damage = 10;
const int princess_damage = 1;

const std::string princess_death_message = "Princess is dead. You lost!";
const std::string hero_death_message = "Hero is dead";
const std::string null_zombie_message = "Coudn`t find zombie";
const std::string delete_error_message = "Trying to delete non existing monster";