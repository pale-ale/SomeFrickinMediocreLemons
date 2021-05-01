#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../server/ServerSettings.h"

class Connector{
    public:
    bool hostGame(int port=ServerSettings::serverPort);
    bool connectToGame(char* address=(char*)"127.0.0.1", int port=ServerSettings::serverPort);
    bool joinGame();
    bool getAuthority(){return authority;}

    private:
    bool authority = false;
    int gameConnectionFd;
    int serverFd;
};