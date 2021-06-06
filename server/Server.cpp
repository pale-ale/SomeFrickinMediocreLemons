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

GameSession Server::createSession(){
    return GameSession();
}

void Server::distributeSessions(){
    int maxSessions = ServerSettings::maxConcurrentSessions - sessions.size();
    if (maxSessions <= 0)
        return;
    log("Server", "Trying to create at most " + to_string(maxSessions) + " session(s)");
    while (queue.size() > ServerSettings::playersPerSession){
        auto newSession = createSession();
        for (int i=0; i<ServerSettings::playersPerSession; ++i){
            newSession.clientFds.push_back(queue.begin()->fd);
            queue.pop_front();
        }
        sessions.push_back(newSession);
    }
}

void Server::updateSession(GameSession& session){
    for (int fd : session.clientFds){
        auto t = connector->rcvMsgServer(fd);
        cout << t << endl;
    }
}

void Server::updateQueue(){
    if (queue.size() == 0){
        queue.push_back(QueueEntry());
    }
    auto queueEntry = queue.begin();
    while (queueEntry != queue.end()){
        if (queueEntry->fd == -1){
            //initialize the socket for this queueentry
            queueEntry->fd = connector->openNewSocket(ServerSettings::serverPort);
        }
        if (!queueEntry->connected){
            //at this point, a socket has a port, but is probably not connect to an endpoint
            int tmpfd = queueEntry->fd;
            if(connector->getConnection(ServerSettings::serverPort, tmpfd)){
                queueEntry->fd = tmpfd;
                queueEntry->connected = true;
                queue.push_back(QueueEntry());
            }
        }
        int currentTime = std::time(NULL);
        if (queueEntry->connected){
            if (currentTime - queueEntry->timeSinceLastAlive > ServerSettings::kickTimeout){
                /* TODO: we probably want a proper disconnect on inactive connections. */
                queue.erase(queueEntry);
            }else{
                auto tcpStringInput = connector->rcvMsgServer(queueEntry->fd);
                if (tcpStringInput != ""){
                    FGeneralDatagram dg;
                    if (!ProtocolBuilder::parseStringToDatagram(tcpStringInput, dg)){
                        cout << "Error in parsing datagram\n";
                        throw;
                    }
                    if (dg.content[0] == 1){
                        OnPlayerRequestJoin(FManagementDatagram(&dg));
                    }
                }
            }
        }
        queueEntry++;
    }
}

void Server::tick(){
    sleep(1);
    updateQueue();
    distributeSessions();
    for (auto &s : sessions){
        updateSession(s);
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
