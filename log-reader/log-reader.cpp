#include <iostream>
#include <fstream>
#include <filesystem>

#include "FileParser.h"

int main()
{
    FileParser parser;
    std::unordered_map<std::string, Player> players;
    std::vector<Team> teams;
    std::vector<Ntmap> maps;
    //std::map<std::string, int> players;
    std::string log_dir = "./logs/";

    parser.readPlayerData("./rosters.txt", &players, &teams);
    parser.readMapData("./maps.txt", &maps);

    std::cout << "Parsing logs..." << std::endl;
    // count files in log dir
    auto dirIter = std::filesystem::directory_iterator(log_dir);
    int n = std::count_if(begin(dirIter), end(dirIter),
        [](auto& entry) { return entry.is_regular_file(); } );
    int i = 0;
    // parse logs
    for (const auto& entry : std::filesystem::directory_iterator(log_dir))
    {
        std::cout <<
            "[" << ++i << "/" << n << "]"
            << entry.path() << std::endl;
        parser.parseLog(entry.path(), &players, &teams, maps);
    }

    parser.saveStats(players, teams, maps);


    // test output
    std::cout << "\nPlease enter a steam id: STEAM_0:";
    std::string input;
    std::cin >> input;
    players.at(input).print(); // todo: validate input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // flush buffer
    std::cin;
}
