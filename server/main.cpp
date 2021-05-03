#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../net/Connector.h"
#include "../Debugging.h"

using namespace Debugging;

int main(int argc, char *argv[])
{
    string progRelativepath(argv[0]);
    string dirRelativePath(progRelativepath.substr(0, progRelativepath.find_last_of("/")) + "/../");
    Settings::programDir = dirRelativePath.c_str();

    cout << "test\n";
    log("Server", "Starting server...");
    Connector connector;
    connector.hostGame();
}