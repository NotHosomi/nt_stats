#include "Player.h"
#include <iostream>
void Player::print() const
{
	std::cout << "+-------------------------------------+\n";
	std::cout << "  Player stats for " << name;
	std::cout << "\n+-------------------------------------+\n";
	std::cout << "Kills:\t  " << kills << "\n";
	std::cout << "Deaths:\t  " << deaths << "\n";
	std::cout << "Suicides: " << suicides << "\n";
	std::cout << "Caps:\t  " << ghost_caps << "\n";
	std::cout << "Assists:  " << assists << "\n";
	std::cout << "TKs:\t  " << TKs << "\n";
	std::cout << "TKed:\t  " << TKed << "\n" << std::endl;
	std::cout << "Maps:\t  " << maps << "\n" << std::endl;

	printKills();
	printDeaths();
}

void Player::printKills() const
{
	std::cout << name << " got kills with:\n";
	for (const auto& iter : weapon_kills)
	{
		std::cout << iter.first << ":\t" << iter.second << "\n";
	}
	std::cout << std::endl;
}

void Player::printDeaths() const
{
	std::cout << name << " was killed by:\n";
	for (const auto& iter : weapon_deaths)
	{
		std::cout << iter.first << ":\t" << iter.second << "\n";
	}
	std::cout << std::endl;
}

std::string Player::csv() const
{
	std::string output;
	const unsigned int* origin = &kills;
	for (int i = 0; i < 8; ++i)
	{
		char* buffer = new char[6];
		sprintf_s(buffer, 6, "%d,", *(origin + i)); // pointer arithmetic is in size of base type
		output += buffer;
	}
	return output;
}
