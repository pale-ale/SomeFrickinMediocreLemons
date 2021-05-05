#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <list>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../server/ServerSettings.h"

class Connector{
    public:
    bool hostGame(int port=ServerSettings::serverPort, int playerNumber = 2);
    bool awaitConnection(int port);

    bool connectToGame(char* address=(char*)"127.0.0.1", int port=ServerSettings::serverPort);
    bool joinGame();
    bool getAuthority(){return authority;}
    bool sndMsg(const char *datagram[34]) const;
    std::string rcvMsg();

    private:
    char buffer[34];
    bool authority = false;
    int clientToServerFd;
    int serverToClientFd;
    std::list<int> clientFds;
};