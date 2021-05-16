#pragma once

#include <memory>

#include "../Debugging.h"
#include "../net/Protocol.h"

class Connector;
class Game;
class Warehouse;

using Debugging::log;

class Server{
    public:
    Server();
    void openLobby();
    void tick();
    void OnPlayerRequestJoin(const FManagementDatagram &dg);
    
    private:
    std::shared_ptr<Warehouse> warehouse = nullptr;
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
};
