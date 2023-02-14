#include "FileParser.h"
#include <filesystem>
#include <iostream>
#include <array>

void FileParser::readPlayerData(std::filesystem::path path, std::unordered_map<std::string, Player>* players, std::vector<Team>* teams)
{
    std::cout << "Mounting team data..." << std::endl;
    std::ifstream file = openFileR(path.string());
    std::string line;
    int team_id = 0;
    while (std::getline(file, line))
    {
        std::pair<std::string, std::string> team_desc = delimitOnce(line, " ");
        int team_size = std::stoi(team_desc.first);
        std::cout << team_desc.second << "... ";
        teams->emplace_back(team_desc.second, team_id);
        for(int i=0; i < team_size; ++i)
        {
            std::getline(file, line);
            std::pair<std::string, std::string> player_info = delimitOnce(line, " ");
            Player p = Player(player_info.first, player_info.second, team_id); // TODO: get teamID from teamname
            players->insert(std::pair<std::string, Player>(player_info.first, p));
            teams->back().roster.emplace_back(&players->at(player_info.first));
        }
        ++team_id;
    }
    std::cout << "Complete." << std::endl;
    this->players = players;
    this->teams = teams;
}

void FileParser::readMapData(std::filesystem::path path, std::vector<Ntmap>* maps)
{
    std::cout << "Mounting map data..." << std::endl;
    std::ifstream file = openFileR(path.string());
    std::string line;
    while (std::getline(file, line))
    {
        maps->emplace_back(line);
    }
    std::cout << "Complete." << std::endl;
}

void FileParser::parseLog(std::filesystem::path path, std::unordered_map<std::string, Player>* players, std::vector<Team>* teams, std::vector<Ntmap>& maps)
{
    // Fetch team tags, use these to ignore mercs
    std::cout << path << std::endl;
    std::string filename = delimit(path.string(), "/").back();
    std::vector<std::string> round_data = delimit(filename, " - "); // can get map name from round_data[1]
    std::pair<std::string, std::string> team_tags = delimitOnce(round_data[0], " vs ");
    for (auto& m : maps)
        if (m.name == round_data[1])
            current_map = &m;
    ++current_map->count;

    for (int i = 0; i < teams->size(); ++i)
    {
        if (team_tags.first == (*teams)[i].name)
        {
            team1 = i;
            ++(*teams)[i].maps;
            incrementMap((*teams)[i].maps_played, round_data[1]);
        }
        if (team_tags.second == (*teams)[i].name)
        {
            team2 = i;
            ++(*teams)[i].maps;
            incrementMap((*teams)[i].maps_played, round_data[1]);
        }
    }
    found_players.clear();
    

    std::ifstream file = openFileR(path.string());
    std::string line;
    //std::vector<std::string> lines;
    int finalReady = 0;
    while (std::getline(file, line))
    {
        if (line.length() == 0 || line[0] != 'L') continue; // not an official log message, skip
        line = line.erase(0,24);
        //lines.emplace_back(line);             // we don't need to seek the last !ready if Oni is trimming logs
        //if (line.find(">\" say \"!ready\""))
        //   finalReady = lines.size();
        parseLine(line); // just parse here instead of creating a seperate line buffer
    }
    //lines.erase(lines.begin(), lines.begin() + finalReady); // don't need this is 

    //for (const auto& line : lines)
    //    parseLine(line);
}

void FileParser::saveStats(const std::unordered_map<std::string, Player>& players, const std::vector<Team>& teams, const std::vector<Ntmap>& maps)
{
    // playerstats
    std::ofstream p_file = openFileW("player_stats.csv");
    std::ofstream t_file = openFileW("team_stats.csv");
    std::ofstream w_file = openFileW("wep_stats.csv");
    p_file << "Name,Team,Kills,Deaths,Suicides,Caps,Assists,TKs,TKed,Maps,\n";
    t_file << "Name,Kills,Deaths,Suicides,Caps,Assists,TKs,TKed,Maps,\n";
    w_file << "Name,Team,";
    std::array<std::string, 22> weapons = { "mpn","srm","srm_s","jitte","jittescoped","zr68c","zr68s","zr68l","mx","mx_silenced","pz","supa7","aa13","srs","m41","m41s","kyla","tachi","milso","grenade","remotedet","knife" };
    for (auto& s : weapons)
        w_file << s + ",";
    w_file << "\n";

    for (auto t = teams.begin(); t != teams.end(); ++t)
    {
        for (auto p = t->roster.begin(); p != t->roster.end(); ++p)
        {
            p_file << (*p)->name + "," + t->name + "," + (*p)->csv() + "\n";
            w_file << (*p)->name + "," + t->name + ",";
            for (auto& s : weapons)
            {
                if (!(*p)->weapon_kills.contains(s))
                    w_file << "0,";
                else
                    w_file << (*p)->weapon_kills.at(s)+",";
            }
            w_file << "\n";                
        }
        t_file << t->name + "," + t->csv() + "\n";
    }


    std::ofstream m_file = openFileW("map_stats.csv");
    m_file << "Name,Plays,Kills,Caps,\n";
    for (auto& m : maps)
    {
        m_file << m.name << "," << m.count << "," << m.kills << "," << m.caps << ",\n";
    }


    p_file.close();
    t_file.close();
    w_file.close();
    m_file.close();
}

void FileParser::parseLine(std::string s)
{
    if (s.find("><STEAM_0:") == std::string::npos) return;// no ID found, server msg
    if (s.find(">\" say \"") != std::string::npos) return;
    if (s.find(">\" say_team \"") != std::string::npos) return;
    if (s.find(">\" changed name to \"") != std::string::npos) return;
    if (s.find(">\" disconnected (reason") != std::string::npos) return;    
    if (s.find(">\" connected, address \"") != std::string::npos) return;
    if (s.find(">\" STEAM USERID validated") != std::string::npos) return;
    if (s.find(">\" STEAM USERID validated") != std::string::npos) return;
    if (s.find(">\" entered the game") != std::string::npos) return;
    if (s.find(">\" joined team \"") != std::string::npos) return;

    std::string message = delimitOnce(s, "><STEAM_0:").second; // drop the player's name
    std::pair<std::string, std::string> id_split = delimitOnce(message, ">\" ");
    std::string id = id_split.first;
    id = delimitOnce(id, "><").first;
    if (!players->count(id))
    {
        // std::cout << "Unregistered player \"" << id << "\" found. Ignoring." << std::endl;
        return;
    }
    std::string event_msg = id_split.second;

    std::pair<std::string, std::string> event_split = delimitOnce(event_msg, " ");
    if (event_split.first == "killed")
        parseKill(id, event_split.second, message);
    else if (event_split.first == "committed")
        parseSuicide(id, event_split.second);
    else if (event_split.first == "triggered")
        parseTrigger(id, event_split.second);
    else
    {
        std::cout << s << std::endl;
        std::cout << "Unexpected event message: " + event_msg << std::endl;
    }

    // add round count to player
    if (!std::count(found_players.begin(), found_players.end(), id))
    {
        Player* p = &players->at(id);
        ++p->maps;
        found_players.emplace_back(id);
    }
}

std::ifstream FileParser::openFileR(std::string name)
{
    std::ifstream file;
    file.open(name, std::ios::in);
    if (!file.is_open())
        throw std::runtime_error("File \"" + name + "\" failed to open");
    return file;
}
std::ofstream FileParser::openFileW(std::string name)
{
    std::ofstream file;
    file.open(name, std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("File \"" + name + "\" failed to open");
    return file;
}

std::vector<std::string> FileParser::delimit(std::string s, std::string delimiter = "\r\n")
{
    std::vector<std::string> tokens;
    size_t pos = s.find(delimiter);
    while (pos != std::string::npos)
    {
        if (pos == std::string::npos)
            break;
        tokens.emplace_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
        pos = s.find(delimiter);
    }
    if(s != "")
        tokens.emplace_back(s);
    return tokens;
}

std::pair<std::string, std::string> FileParser::delimitOnce(std::string s, std::string delimiter = "\r\n")
{
    std::pair<std::string, std::string> tokens;
    size_t pos = s.find(delimiter);
    if (pos == std::string::npos)
    {
        std::cout << "Bad delimit: " << s << std::endl;
        throw std::runtime_error("Bad split on \"" + s + "\" with delimiter \"" + delimiter + "\"");
    }
    tokens.first = s.substr(0, pos);
    tokens.second = s.substr(pos + delimiter.length(), s.length());
    return tokens;
}

void FileParser::parseKill(std::string player_id, std::string details, std::string base_message)
{
    ++current_map->kills;

    std::string debug = details;
    //L 01/04/2023 - 17:11:25: "Ghost Lizard<34><STEAM_0:1:20336729><NSF>" killed "masterslay<17><STEAM_0:1:2331419><Jinrai>" with "zr68s"
    details = delimitOnce(details, "><STEAM_0:").second;
    std::string victim_id = delimitOnce(details, "><").first;
    std::string weapon = delimit(details, "\"")[2];

    bool valid_p = players->contains(player_id);
    bool valid_v = players->contains(victim_id);

    Player* p = nullptr;
    if (valid_p)
    {
        p = &players->at(player_id);
        if (p->team_id == team1 || p->team_id == team2)
            ++p->kills;
    }
    else
    {
        std::cout << "Invalid killer \"" << player_id << "\"" << std::endl;
    }

    Player* v = nullptr;
    if (valid_v)
    {
        v = &players->at(victim_id);
        if (v->team_id == team1 || v->team_id == team2)
            ++v->deaths;

        // add round count to player (incase that player got 0 kills, caps, suis, assists, etc)
        if (!std::count(found_players.begin(), found_players.end(), victim_id))
        {
            ++v->maps;
            found_players.emplace_back(victim_id);
        }
    }
    else
    {
        std::cout << "Invalid victim in \"" << debug << "\"" << std::endl;
    }

    // teamkills
    // teamkill check uses 
    int NSF_count = delimit(base_message, "><NSF>\" ").size()-1;
    if (NSF_count != 1)
    {
        if (valid_p && (p->team_id == team1 || p->team_id == team2))
            ++p->TKs;
        if (valid_v && (v->team_id == team1 || v->team_id == team2))
            ++v->TKed;
        return; // don't wep track TKs
    }

    // weapon tracking
    if (valid_p && (p->team_id == team1 || p->team_id == team2))
        incrementMap(p->weapon_kills, weapon);
    if (valid_v && (v->team_id == team1 || v->team_id == team2))
        incrementMap(v->weapon_deaths, weapon);
}

void FileParser::parseSuicide(std::string player_id, std::string method)
{
    //L 01/04/2023 - 17:10:36: "[ANUS] Wahaha-!!<19><STEAM_0:1:17526508><Jinrai>" committed suicide with "world"
    if (!players->contains(player_id))
        return;
    Player* p = &players->at(player_id);
    ++p->suicides;
    ++p->deaths;
}

void FileParser::parseTrigger(std::string player_id, std::string event_name)
{
    if (!players->contains(player_id))
        return;
    Player* p = &players->at(player_id);
    //L 01/04/2023 - 17:11:51: "The Worst -<35><STEAM_0:1:196697321><NSF>" triggered "kill_assist"
    //L 01/04/2023 - 17:20:37: "[DYS] Infrequent<18><STEAM_0:1:6384081><NSF>" triggered "ghost_capture"
    if (event_name == "\"kill_assist\"")
    {
        ++p->assists;
    }
    else if (event_name == "\"ghost_capture\"")
    {
        ++p->ghost_caps;
        ++current_map->caps;
    }
}

void FileParser::incrementMap(std::unordered_map<std::string, int>& map, std::string key)
{
    std::unordered_map<std::string, int>::iterator iter = map.find(key);
    // key already present on the map
    if (iter != map.end()) {
        ++iter->second;    // increment map's value for key
    }
    // key not found
    else {
        map.insert(std::make_pair(key, 1));
    }
}