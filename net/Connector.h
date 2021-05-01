#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../Settings.h"
#include "../server/ServerSettings.h"

class Connector{
    public:
    void hostGame(int port=ServerSettings::serverPort);
    int connectToGame(char* address=(char*)"127.0.0.1", int port=ServerSettings::serverPort);
};