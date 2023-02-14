#pragma once

#include <vector>
#include "Player.h"

class Team {
public:
	Team(std::string name, int id) : name(name), id(id) {};
	std::string name;
	int id;
	std::vector<Player*> roster;

	std::string csv() const;

	int totalKills() const;
	int totalDeaths() const;
	int totalSui() const;
	int totalCaps() const;
	int totalAssists() const;
	int totalTK() const;
	int totalTKed() const;
	int maps = 0;
	std::unordered_map<std::string, int> maps_played;
};