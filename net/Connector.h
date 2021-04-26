#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class Connector{
    public:
    void hostGame(int port = 12357);
    void connectToGame();
};