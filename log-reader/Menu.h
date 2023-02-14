#pragma once
#include <vector>
#include <string>

class Menu
{
public:
	Menu() = default;

private:
	int readInt();
	bool readBool();

	std::string menu_title;
	std::vector<std::string> options;
};

