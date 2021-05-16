#include "Server.h"
#include "../net/Connector.h"
#include "../Game.h"
#include "Warehouse.h"


Server::Server(){
    log("Server", "Starting server...");
    connector = std::make_shared<Connector>();
    warehouse = std::make_shared<Warehouse>();
    if (!warehouse->setDataSource("/home/alba/projects/SomeFrickinMediocreLemons/playerData/PlayerData.json")){
        log("Server", "Error setting datapath");
        throw;
    }
    warehouse->readData();
}

void Server::openLobby(){
    connector->hostGame(13579,1);
}

void Server::tick(){
    std::cout << "Awaiting message...\n";
    auto tcpStringInput = connector->rcvMsg();
    std::cout << tcpStringInput[0] << "...\n";
    FGeneralDatagram dg;
    /*  FManagementDatagram joinRequest = FGeneralDatagram(EDatagramType::Management, rcvMsg().c_str());
    log("Connector", "The client tries to join with PlayerID: '" + to_string(joinRequest.playerID) + "' .");
    */
    if (!ProtocolBuilder::parseStringToDatagram(tcpStringInput, dg)){
        cout << "Error in parsing datagram\n";
        throw;
    }
    if (dg.content[0] == 1){
        OnPlayerRequestJoin(FManagementDatagram(&dg));
    }
}

void Server::OnPlayerRequestJoin(const FManagementDatagram &dg){
    auto playerID = dg.getPlayerID();
    log("Server", "Player with ID \'" + to_string(playerID) + "\' is trying to join.");
    auto playerInfo = warehouse->getPlayerInfo(playerID);
    if (playerInfo.playerName != ""){
        log("Server", "This player is already known as \'" + string(playerInfo.playerName) + "\'.");
    }else{
        log("Server", "Player not already known.");
    }
}
