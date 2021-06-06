#pragma once

#include <memory>
#include <ctime>
#include <list>

#include "../Debugging.h"
#include "../net/Protocol.h"

class Connector;
class Game;
class Warehouse;

using Debugging::log;

struct GameSession{
    std::vector<int> tempClientFds;
    std::vector<int> clientFds;
    bool openToJoin = true;
    bool bound = false;
    int maxPlayers = 1;
};

struct QueueEntry{
    QueueEntry(){
        timeSinceLastAlive = std::time(NULL);
    }
    int fd = -1;
    bool verified = false;
    bool connected = false;
    int timeSinceLastAlive = 0;
};

class Server{
    public:
    Server();
    void distributeSessions();
    void tick();
    void acceptPlayerConnection();
    void OnPlayerRequestJoin(const FManagementDatagram &dg);
    
    private:
    GameSession createSession();
    void updateQueue();
    void updateSession(GameSession &session);

    std::shared_ptr<Warehouse> warehouse = nullptr;
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
    std::vector<GameSession> sessions = {};
    std::list<QueueEntry> queue = {};
};
