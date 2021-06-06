#include "Connector.h"
#include "../Debugging.h"

using Debugging::log;

/* Opens a new port, binds to it and listens there. Returns -1 on error.*/
int Connector::openNewSocket(int port){
    int new_socket;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    new_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    
    if (new_socket == -1)
    {
        log("Connector", "Couldn't create socket.");
        return -1;
    }
    
    if (setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        log("Connector", "Couldn't setsockopt.");
        perror("socket");
        return -1;
    }
    
    if (bind(new_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        log("Connector", "Couldn't bind to socket");
        perror("socket");
        return -1;
    }
    log("Connector", "Bound to port " + to_string(port));

    if (listen(new_socket, 3) < 0)
    {
        perror("conn");
        log("Connector", "Couldn't listen.");
        return false;
    }
    log("Connector", "Listening for incoming connections on port '" + to_string(port) + "'...");
    
    return new_socket;
}

/* Tries to accept a connection at a port. Non-blocking. */
bool Connector::getConnection(int port, int &inFd){    
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    inFd = accept4(inFd, (struct sockaddr *)&address, (socklen_t*)&addrlen, SOCK_NONBLOCK);
    if (inFd < 0){
        if (errno == EWOULDBLOCK)
        {
            return false;
        }
        perror("Server:Socket");
        log("Connector", "Socket accept error");
        return false;
    }
    log("Connector", "A client connected.");
    return true;
}

/* Tries to establish a connection to a remote server. Client-only */
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

/* When the TCP-level connection with a server is established, ask whether the player can join the game */ 
void Connector::sendJoinQueueRequest(){
    if (connectionstate == EConnectionState::Joining){
        log("Connector", "sendJoinQueueRequest(): Join already in progress.");
        return;
    }
    if (connectionstate != EConnectionState::Connected || clientToServerFd < 1){
        log("Connector", "sendJoinQueueRequest(): Cannot join a game when not connected.");
        return;
    }
    auto msg = ProtocolBuilder::assembleJoinRequest(123);
    sndMsgClient(msg.data);
    log("Connector", "Trying to join with PlayerID " + to_string(msg.getPlayerID()));
    connectionstate = EConnectionState::Joining;
}

void Connector::sndMsgClient(const char datagram[35]) const{
    send(clientToServerFd, datagram, sizeof(char)*35, 1);
}

/* Receive bytes from clientFd. Non-blocking. Server-only. */ 
char* Connector::rcvMsgServer(int clientFd){
    buffer[0] = '\0';
    int ret = read(clientFd, buffer, sizeof(char)*35);
    if (ret < 0 && errno != EWOULDBLOCK){
        perror("socket");
        log("Connector", "rcvMsg() received error code " + to_string(ret) + " on fd " + to_string(clientFd));
    }
    return buffer;
}

/* Receive bytes from serverFd. Non-blocking. Client-only. */
char* Connector::rcvMsgClient(){
    int ret = read(clientToServerFd, buffer, sizeof(char)*35);
    if (ret < 0){
        log("Connector", "rcvMsg() received error code " + to_string(ret));
    } 
    return buffer;
}
