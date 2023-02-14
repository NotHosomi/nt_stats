#pragma once
#include "Player.h"
#include <map>

class GlobalStats
{
	void addField(std::string key, int value);
	void compare(std::string key, int value, Player* player);

	std::map<std::string, int> stats;
	std::map<std::string, std::vector<Player*>> owner;

	// most X on a map
	// kills, deaths, caps, etc
};

