#pragma once

#include <string>
#include <unordered_map>

class Player
{
public:
	Player(std::string id, std::string player_name, int team)
	{
		steam_id = id;
		name = player_name;
		team_id = team;
	}

	void print() const;
	void printKills() const;
	void printDeaths() const;
	std::string csv() const;

	std::string steam_id;
	std::string name;
	int team_id;
	unsigned int kills = 0;
	unsigned int deaths = 0;
	unsigned int suicides = 0;
	unsigned int ghost_caps = 0;
	unsigned int assists = 0;
	unsigned int TKs = 0;
	unsigned int TKed = 0;
	unsigned int maps = 0;

	std::unordered_map<std::string, int> weapon_kills;
	std::unordered_map<std::string, int> weapon_deaths;
};

