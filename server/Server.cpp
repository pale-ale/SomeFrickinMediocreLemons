#include "Server.h"
#include "../net/Connector.h"
#include "../Game.h"

Server::Server(){
    log("Server", "Starting server...");
    connector = move(std::make_shared<Connector>());
}

void Server::openLobby(){
    connector->hostGame();
}