#include "Connector.h"

void Connector::hostGame(int port){
    std::cout << "Hosting TBD; Please start server manually instead.\n";
}

int Connector::connectToGame(char* address, int serverPort){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = (char*)"Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
       
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    std::cout << "Connector: Trying to join on address " << address << ":" << serverPort << "...\n";
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Connector: Joined successfully.\n");
    send(sock , hello , strlen(hello) , 0 );
    valread = read( sock , buffer, 1024);
    printf("Connector: %s\n",buffer );
    return 0;
}