#include "Menu.h"
#include <iostream>

int Menu::readInt()
{
    std::string input;
    while (1)
    {
        std::cout << "" << std::endl;
        std::cin >> input;
        int value = atoi(input.c_str());
        if (value < 1 || value > options.size())
        {
            std::cout << "Please enter a valid number..." << std::endl;
            continue;
        }
    } 
}

bool Menu::readBool()
{
    return false;
}
