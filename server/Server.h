#pragma once

#include <memory>

#include "../Debugging.h"

class Connector;
class Game;

using Debugging::log;

class Server{
    public:
    Server();
    void openLobby();
    
    private:
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
};
