#pragma once
#include "Player.h"

class Ntmap
{
public:
	Ntmap(std::string name);
	std::string name;
	unsigned int kills;
	unsigned int caps;
	unsigned int count;
	std::unordered_map<std::string, unsigned int> weapon_kills;
};

