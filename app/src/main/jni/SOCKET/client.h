// Created By DAKRISDE / BAPAN FF
#ifndef TCP_SOCKET_CLIENT_H
#define TCP_SOCKET_CLIENT_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


class SocketClient {
public:
    int sockfd;
    char socket_name[108]; // 108 sun_path length max
    bool created,connected;

    SocketClient();

    bool Create();
    bool Connect();
    void Close();

    int sendData(void *inData, size_t size);
    bool sendX(void* inData, size_t size);

    int recvData(void *outData, size_t size);
    size_t receive(void* outData);
};
#endif //TCP_SOCKET_CLIENT_H
