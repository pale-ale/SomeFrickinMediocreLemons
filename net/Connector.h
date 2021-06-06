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
    // +++ Server-only functions +++

    int openNewSocket(int port);
    bool getConnection(int port, int &inFd);
    void sendJoinAccept(int fd);
    void sendJoinDeny(int fd);
    char* rcvMsgServer(int clientFd);

    /* Client-only functions */

    bool connectToGame(char* address=(char*)"127.0.0.1", int port=ServerSettings::serverPort);
    void sendJoinQueueRequest();
    void sndMsgClient(const char datagram[35]) const;
    char* rcvMsgClient();

    /* Server/Client functions */

    EConnectionState getConnectionState();
    bool getAuthority(){return authority;}
    void getDatagramType();

    private:

    EConnectionState connectionstate = EConnectionState::Disconnected;
    char buffer[35];
    bool authority = false;
    int clientToServerFd;
};