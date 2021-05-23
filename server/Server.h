#pragma once

#include <memory>

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

class Server{
    public:
    Server();
    void createSessions(int count);
    void tryBindSessions();
    void tryConnectSessions();
    void tick();
    void acceptPlayerConnection();
    void OnPlayerRequestJoin(const FManagementDatagram &dg);
    bool bHasIncomingConnection();
    
    private:
    GameSession createSession();
    void tryBindSession(GameSession &inSession);
    void tryConnectSession(GameSession &inSession);

    std::shared_ptr<Warehouse> warehouse = nullptr;
    std::shared_ptr<Connector> connector = nullptr;
    std::shared_ptr<Game> game = nullptr;
    std::vector<GameSession> sessions = {};
};
