#include <iostream>
#include <netinet/in.h>
#include "../Debugging.h"
#include "../GlobalFunctions.h"

#include "Server.h"

using namespace Debugging;

int main(int argc, char *argv[])
{
    Settings::programDir = getDirFromArg(argv[0]).c_str();
    Server server;
    server.openLobby();
    //while (true){
        server.tick();
    //}
}