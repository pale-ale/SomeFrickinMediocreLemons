#include "Connector.h"
#include "../Debugging.h"

using Debugging::log;
/*
Opens a listen port and tries to accept a connection there.
This is a non-blocking operation.
*/
bool Connector::getConnection(int port, int &inFd){
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket, valread;
    int opt = 1;
       
    if ((serverToClientFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log("Connector", "Couldn't create socket.");
        return false;
    }
    if (setsockopt(serverToClientFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | SOCK_NONBLOCK,
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
    log("Connector", "Listening for incoming connections on port '" + to_string(port) + "'...");
    if ((new_socket = accept(serverToClientFd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        log("Connector", "Could not accept connection or timeout.");
        return false;
    }
    log("Connector", "A client connected.");
    inFd = new_socket;
    return true;
}

/*
Opens a new game session for a number of players.
*/
bool Connector::hostGame(int port, int playerNumber){
    authority = true;
    while (clientFds.size() < playerNumber){
        getConnection(port);
    }
    log("Connector", "All players connected. Starting game...");
    return true;
}

/*
Tries to establish a connection to a remote server. 
Only call from client
*/
bool Connector::connectToGame(char* address, int serverPort){
    if (clientToServerFd > 0){
        log("Connector", "Already connected to a game.");
        //return false;
    }
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
    log("Connector", "Trying to join " + (string)address + ":" + std::to_string(serverPort) + "...");
    if (connect(clientToServerFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        log("Connector", "Connection Failed.");
        return false;
    }
    struct sockaddr_in sin;
    int addrlen = sizeof(sin);
    getsockname(clientToServerFd, (struct sockaddr*) &sin, (socklen_t*)&addrlen);
    log("Connector", "Connected successfully via port " + to_string(ntohs(sin.sin_port)) + ".");
    connectionstate = EConnectionState::Connected;
    return true;
}

void Connector::sendJoinRequest(){
    if (connectionstate == EConnectionState::Joining){
        log("Connector", "joinGame(): Join already in progress.");
        return;
    }
    if (connectionstate != EConnectionState::Connected || clientToServerFd < 1){
        log("Connector", "joinGame(): Cannot join a game when not connected.");
        return;
    }
    auto msg = ProtocolBuilder::assembleJoinRequest(123);
    sndMsg(msg.data);
    log("Connector", "Trying to join with PlayerID " + to_string(msg.getPlayerID()));
    connectionstate = EConnectionState::Joining;
}

bool Connector::sndMsg(const char datagram[35]) const{
    if (authority){
        send(serverToClientFd, datagram, sizeof(char)*35, 1);
    }else{
        send(clientToServerFd, datagram, sizeof(char)*35, 1);
    }
    return false;
}

/*
Receive bytes from clientFd.
Non-blocking.
Server only.
*/ 
const char* Connector::rcvMsgServer(int clientFd){
    int ret = read(clientFd, buffer, sizeof(char)*35);
    if (ret < 0){
        log("Connector", "rcvMsg() received error code " + to_string(ret));
    } 
    return buffer;
}
/*
Receive bytes from serverFd.
Non-blocking.
Client only.
*/
const char* Connector::rcvMsgClient(){
    int ret = read(clientToServerFd, buffer, sizeof(char)*35);
    if (ret < 0){
        log("Connector", "rcvMsg() received error code " + to_string(ret));
    } 
    return buffer;
}

void Connector::process(){

}

