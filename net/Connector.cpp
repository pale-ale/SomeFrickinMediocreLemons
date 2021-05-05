#include "Connector.h"
#include "../Debugging.h"

using Debugging::log;

bool Connector::awaitConnection(int port){
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket, valread;
    int opt = 1;
       
    if ((serverToClientFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log("Connector", "Couldn't create socket.");
        return false;
    }
    if (setsockopt(serverToClientFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        log("Connector", "Couldn't setsockopt.");
        return false;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
       
    if (bind(serverToClientFd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        log("Connector", "Couldn't bind to socket");
        return false;
    }
    if (listen(serverToClientFd, 3) < 0)
    {
        log("Connector", "Couldn't listen.");
        return false;
    }
    log("Server", (string)"Listening for incoming connections on port '" + std::to_string(port) + "'...");
    if ((new_socket = accept(serverToClientFd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        log("Connector", "Could not accept connection or timeout.");
        return false;
    }
    log("Server", "A client connected.");
    clientFds.push_back(new_socket);
    return true;
}

bool Connector::hostGame(int port, int playerNumber){
    log("Server", "Hosting a game for " + to_string(playerNumber) + " players.");
    while (clientFds.size() < playerNumber){
        awaitConnection(port);
    }
    log("Server", "All players connected. Starting game...");
    return true;
}

bool Connector::connectToGame(char* address, int serverPort){
    struct sockaddr_in serv_addr;
    if ((clientToServerFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        log("Connector", "Socket creation error.");
        return false;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
       
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0) 
    {
        log("Connector", "Invalid address/ Address not supported.");
        return false;
    }
   
    log("Connector", "Trying to join on address" + (string)address + ":" + std::to_string(serverPort) + "...");
    if (connect(clientToServerFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        log("Connector", "Connection Failed.");
        return false;
    }
    log("Connector", "Joined successfully.");
    return true;
}

bool Connector::sndMsg(const char *datagram[34]) const{
    if (authority){
        send(serverToClientFd, datagram, sizeof(char)*34, 1);

    }
    return false;
}

string Connector::rcvMsg(){
    return "";
}