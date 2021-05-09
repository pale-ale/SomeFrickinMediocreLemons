#include "Server.h"
#include "../net/Connector.h"
#include "../Game.h"

Server::Server(){
    log("Server", "Starting server...");
    connector = move(std::make_shared<Connector>());
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
    cout << (int)dg.content[0] << " " << dg.content << endl;
}

void Server::OnPlayerRequestJoin(const FGeneralDatagram &dg){

}
