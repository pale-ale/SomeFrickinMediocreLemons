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

void Server::createSessions(int count){
    assert(count > 0);
    log("Server", "Creating " + to_string(count) + " sessions");
    for (int i=0; i<count; ++i){
        auto newSession = createSession();
        sessions.push_back(newSession);
    }
}

void Server::tryConnectSession(GameSession &inSession){
    for (int i = 0; i<inSession.tempClientFds.size(); ++i){
        if(inSession.clientFds[i] == -1){
            int tmpFd = inSession.tempClientFds[i];
            if(connector->getConnection(ServerSettings::serverPort, tmpFd)){
                cout << "Accepted a connection.\n";
                inSession.clientFds[i] = tmpFd;
            }
        }
    }
}

void Server::tryConnectSessions(){
    for (auto &session : sessions){
        tryConnectSession(session);
    }
}

void Server::tryBindSession(GameSession &inSession){
    if (!inSession.bound){            
        for (int i=0; i < inSession.maxPlayers; ++i){
            int newFd = connector->openNewSocket(ServerSettings::serverPort);
            if (newFd == -1){
                log("Server", "Error binding to socket in this session");
            }else{
                inSession.tempClientFds.push_back(newFd);
                inSession.clientFds.push_back(-1);
            }
            inSession.bound = true;
        }
    }
}

void Server::tryBindSessions(){
    for (auto &session : sessions){
        tryBindSession(session);
    }
}

void Server::tick(){
    sleep(1);
    int sessionsToCreate = ServerSettings::maxConcurrentSessions - sessions.size();
    if (sessionsToCreate > 0){
        createSessions(sessionsToCreate);
    }
    tryBindSessions();
    tryConnectSessions();
    for (auto &s : sessions){
        std::cout << "Awaiting message...\n";
        /*auto tcpStringInput = connector->rcvMsgServer();
        FGeneralDatagram dg;
        if (!ProtocolBuilder::parseStringToDatagram(tcpStringInput, dg)){
            cout << "Error in parsing datagram\n";
            throw;
        }
        if (dg.content[0] == 1){
            OnPlayerRequestJoin(FManagementDatagram(&dg));
        }*/
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

bool Server::bHasIncomingConnection(){
    int test = 0;
    cout << "Incoming: " << connector->getConnection(13579, test) << endl;
}
