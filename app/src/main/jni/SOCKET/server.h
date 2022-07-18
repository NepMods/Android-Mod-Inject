// Created By DAKRISDE / BAPAN FF

#ifndef TCP_SOCKET_SERVER_H
#define TCP_SOCKET_SERVER_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

class SocketServer {
public:
    int listenfd, acceptfd;
    bool isCreated;
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

    SocketServer();

    bool Create();
    bool Accept();
    bool Bind();
    bool Listen();
    void Close();

    int sendData(void *inData, size_t size);
    bool sendX(void* inData, size_t size);

    int recvData(void *outData, size_t size);
    size_t receive(void* outData);
};


#endif //TCP_SOCKET_SERVER_H



