#include "Connector.h"
#include "../Debugging.h"

using Debugging::log;

/* Open a new port, bind to it and listen there. Returns -1 on error.*/
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

/*
    Tries to accept a connection at a port.
    This is a non-blocking operation.
*/
bool Connector::getConnection(int port, int &inFd){    
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    
    //new_socket = accept4(new_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen, SOCK_NONBLOCK);
    cout << "test: infd = " << inFd << endl;
    inFd = accept(inFd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    cout << "test: infd2 = " << inFd << endl;
    if (inFd < 0){
        if (errno == EWOULDBLOCK)
        {
            //log("Connector", "Could not accept connection or timeout. Code " + error to_string(new_socket));
            cout << "No connection to accept\n";
            return false;
        }
        perror("Server:Socket");
        return false;
    }
    log("Connector", "A client connected.");
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

/* When the TCP-level connection with a server is established, ask whether the player can join the game*/ 
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
    sndMsgClient(msg.data);
    log("Connector", "Trying to join with PlayerID " + to_string(msg.getPlayerID()));
    connectionstate = EConnectionState::Joining;
}

void Connector::sndMsgClient(const char datagram[35]) const{
    send(clientToServerFd, datagram, sizeof(char)*35, 1);
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

