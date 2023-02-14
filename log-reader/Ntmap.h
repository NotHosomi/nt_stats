#pragma once
#include "Player.h"

class Ntmap
{
public:
	Ntmap(std::string name);
	std::string name;
	unsigned int kills = 0;
	unsigned int caps = 0;
	unsigned int count = 0;
	std::unordered_map<std::string, unsigned int> weapon_kills;
};

