#include "GlobalStats.h"
#include <stdexcept>

void GlobalStats::addField(std::string key, int value)
{
	stats.insert(std::pair<std::string, int>(key, 0));
	std::vector<Player*> empty;
	owner.insert(std::pair<std::string, std::vector<Player*>>(key, empty));
}

void GlobalStats::compare(std::string key, int value, Player* player)
{
	auto stat = stats.find(key);
	if (stat == stats.end())
		throw std::runtime_error("invalid key: " + key);

	if (value < stat->second)
		return;
	if (value > stat->second)
	{
		stat->second = value;
		owner.find(key)->second.clear();
	}
	owner.find(key)->second.emplace_back(player);
}
