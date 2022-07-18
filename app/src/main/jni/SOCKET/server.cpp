#include "server.h"
// Created By DAKRISDE / BAPAN FF

SocketServer::SocketServer(){
    isCreated = false;
}

bool SocketServer::Create() {
    isCreated = (listenfd = socket(AF_INET, SOCK_STREAM, 0)) != -1;
    return isCreated;
}

bool SocketServer::Bind() {
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(65035);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    if (bind(listenfd, (sockaddr*)&hint, sizeof(hint)) == -1) {
        Close();
        return false;
    }
    return true;
}

bool SocketServer::Listen() {
    if (listen(listenfd, SOMAXCONN) == -1) {
        Close();
        return false;
    }
    return true;
}

bool SocketServer::Accept() {
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    if ((acceptfd = accept(listenfd, (sockaddr*)&client, &clientSize)) == -1) {
        Close();
        return false;
    }
    host[NI_MAXHOST];      // Client's remote name
    service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        std::cout << host << " connected on port " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }
    return true;
}

int SocketServer::sendData(void *inData, size_t size) {
    char *buffer = (char *) inData;
    int numSent = 0;
    while (size) {
        do {
            numSent = send(acceptfd, buffer, size, 0);
        } while (numSent == -1 && EINTR == errno);

        if (numSent <= 0) {
            Close();
            break;
        }
        size -= numSent;
        buffer += numSent;
    }
    return numSent;
}

bool SocketServer::sendX(void* inData, size_t size) {
    uint32_t length = htonl(size);
    if(sendData(&length, sizeof(uint32_t)) <= 0){
        return false;
    }
    return sendData((void*)inData, size) > 0;
}

int SocketServer::recvData(void *outData, size_t size) {
    char *buffer = (char *) outData;
    int numReceived = 0;
    while (size) {
        memset(buffer, 0, size);
        do {
            numReceived = recv(acceptfd, buffer, size, 0);
        } while (numReceived == -1 && EINTR == errno);

        if (numReceived <= 0) {
            Close();
            break;
        }

        size -= numReceived;
        buffer += numReceived;
    }
    return numReceived;
}

size_t SocketServer::receive(void* outData) {
    uint32_t length = 0;
    int code = recvData(&length, sizeof(uint32_t));
    if(code > 0){
        length = ntohl(length);
        recvData(outData, static_cast<size_t>(length));
    }
    return length;
}

void SocketServer::Close() {
    if (acceptfd > 0)
        close(acceptfd);
    if (listenfd > 0)
        close(listenfd);
}