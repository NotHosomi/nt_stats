#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Player.h"
#include "Team.h"
#include "Ntmap.h"

class FileParser
{
public:
	void readPlayerData(std::filesystem::path path, std::unordered_map<std::string, Player>* players, std::vector<Team>* teams);
	void readMapData(std::filesystem::path path, std::vector<Ntmap>* maps);
	void parseLog(std::filesystem::path path, std::unordered_map<std::string, Player>* players, std::vector<Team>* teams, std::vector<Ntmap>& maps);
	void saveStats(const std::unordered_map<std::string, Player>& players, const std::vector<Team>& teams, const std::vector<Ntmap>& maps);

private:
	void parseLine(std::string);

	std::ifstream openFileR(std::string dir);
	std::ofstream openFileW(std::string dir);
	std::vector<std::string> delimit(std::string, std::string delimiter);
	std::pair<std::string, std::string> delimitOnce(std::string s, std::string delimiter);

	void parseKill(std::string player_id, std::string details, std::string base_message);
	void parseSuicide(std::string player_id, std::string method);
	void parseTrigger(std::string player_id, std::string event_name);

	std::unordered_map<std::string, Player>* players = nullptr;
	std::vector<Team>* teams = nullptr;
	int team1;
	int team2;

	void incrementMap(std::unordered_map<std::string, int>& map, std::string key);
	int countMap(std::unordered_map<std::string, int>& map, std::string key);
	std::vector<std::string> found_players;
	Ntmap* current_map;
};

