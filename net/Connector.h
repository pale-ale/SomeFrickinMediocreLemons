#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <list>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Protocol.h"

#include "../server/ServerSettings.h"

enum EConnectionState{
    Joining,
    Connected,
    Disconnecting,
    Disconnected
};

class Connector{
    public:
    bool hostGame(int port=ServerSettings::serverPort, int playerNumber = 2);
    bool getConnection(int port, int &inFd);

    bool connectToGame(char* address=(char*)"127.0.0.1", int port=ServerSettings::serverPort);
    void sendJoinRequest();
    bool getAuthority(){return authority;}
    EConnectionState getConnectionState();
    bool sndMsg(const char datagram[35]) const;
    const char* rcvMsgServer(int clientFd);
    const char* rcvMsgClient();

    void process();
    void getDatagramType();

    private:
    EConnectionState connectionstate = EConnectionState::Disconnected;
    char buffer[35];
    bool authority = false;
    int clientToServerFd;
    int serverToClientFd;
};