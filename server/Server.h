#pragma once

#include <memory>

#include "../Debugging.h"
#include "../net/Protocol.h"

class Connector;
class Game;

using Debugging::log;

class Server{
    public:
    Server();
    void openLobby();
    void tick();
    void OnPlayerRequestJoin(const FGeneralDatagram &dg);
    
    private:
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
};
