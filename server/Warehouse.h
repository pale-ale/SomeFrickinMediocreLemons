#pragma once

#include <vector>
#include "../thirdParty/json.hpp"
#include <fstream>

using nlohmann::json;

struct FPlayerInfo{
    unsigned short playerID = 0;
    std::string playerName = "";
    std::vector<int> deck = {};
};

struct FPlayerData{
    std::vector<FPlayerInfo> playerInfo;
};

inline void from_json(const json& j, FPlayerInfo& p) {
    j.at("id").get_to(p.playerID);
    j.at("name").get_to(p.playerName);
    j.at("deck").get_to(p.deck);
}

inline void from_json(const json& j, FPlayerData& p) {
    j.at("playerData").get_to(p.playerInfo);
}

class Warehouse{
    public:
    bool setDataSource(const char *path);
    void readData();
    FPlayerInfo getPlayerInfo(unsigned short playerID);

    private:
    char *path = nullptr;
    std::ifstream filestream;
    FPlayerData pd;
};