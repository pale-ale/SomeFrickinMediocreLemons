#pragma once

#include <memory>

#include "../Debugging.h"
#include "../net/Protocol.h"

class Connector;
class Game;
class Warehouse;

using Debugging::log;

struct GameSession{
    std::vector<int> clientFds;
    bool openToJoin = true;
    int maxPlayers = 1;
};

class Server{
    public:
    Server();
    void openLobby();
    void tick();
    void acceptPlayerConnection();
    void OnPlayerRequestJoin(const FManagementDatagram &dg);
    
    private:
    std::shared_ptr<Warehouse> warehouse = nullptr;
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
    std::vector<GameSession> sessions = {};
};
