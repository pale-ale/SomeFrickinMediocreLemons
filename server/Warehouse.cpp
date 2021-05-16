#include "Warehouse.h"
#include <iostream>
#include "../Debugging.h"

using Debugging::log;

FPlayerInfo Warehouse::getPlayerInfo(unsigned short playerID){
    for (auto &playerInfo : pd.playerInfo){
        if (playerInfo.playerID == playerID){
            return playerInfo;
        }
    }
    return FPlayerInfo();
}

bool Warehouse::setDataSource(const char *path){
    log("Warehouse", "Setting data source to \'" + string(path) + "\'");
    filestream.close();
    filestream.open(path, std::ios_base::in);
    return filestream.is_open() && !filestream.fail();
}

void Warehouse::readData(){
    json j;
    filestream >> j;
    j.get_to(pd);
}