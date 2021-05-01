#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ServerSettings.h"
#include "../net/Connector.h"

int main(int argc, char *argv[])
{
    Connector connector;
    connector.hostGame();
}