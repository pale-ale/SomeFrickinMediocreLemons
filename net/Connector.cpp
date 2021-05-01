#include "Connector.h"

bool Connector::hostGame(int port){
    std::cout << "Hosting TBD; Please start server manually instead.\n";
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int server_fd, new_socket, valread;
    int opt = 1;
    char buffer[1024] = {0};
    char *hello = (char*)"Hello from server";
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Server: Couldn't create socket.");
        return false;
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("Server: Couldn't setsockopt.");
        return false;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
       
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("Server: Couldn't bind to socket");
        return false;
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("Server: Couldn't listen.");
        return false;
    }
    std::cout << "Server: Listening for incoming connections on port '" << port << "'...\n";
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("Server: Could not accept connection or timeout.");
        return false;
    }
    valread = read( new_socket , buffer, 1024);
    printf("Server: %s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    return true;
}

bool Connector::connectToGame(char* address, int serverPort){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = (char*)"Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return false;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
       
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }
   
    std::cout << "Connector: Trying to join on address " << address << ":" << serverPort << "...\n";
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return false;
    }
    printf("Connector: Joined successfully.\n");
    send(sock , hello , strlen(hello) , 0 );
    valread = read( sock , buffer, 1024);
    printf("Connector: %s\n",buffer );
    return true;
}