#include "client.h"
// Created By DAKRISDE / BAPAN FF

SocketClient::SocketClient(){
    created = false;
    connected = false;
}

bool SocketClient::Create() {
    created = (sockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1;
    return created;
}

bool SocketClient::Connect() {
    int port = 65035;
    std::string ipAddress = "127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    if (connect(sockfd, (sockaddr*)&hint, sizeof(hint)) == -1) {
        Close();
        return false;
    }
    connected = true;
    return true;
}


int SocketClient::sendData(void *inData, size_t size) {
    char *buffer = (char *) inData;
    int numSent = 0;

    while (size) {
        do {
            numSent = send(sockfd, buffer, size, 0);
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

bool SocketClient::sendX(void *inData, size_t size) {
    uint32_t length = htonl(size);
    if(sendData(&length, sizeof(uint32_t)) <= 0){
        return false;
    }
    return sendData((void*)inData, size) > 0;
}


int SocketClient::recvData(void *outData, size_t size) {
    char *buffer = (char *) outData;
    int numReceived = 0;

    while (size) {
        do {
            numReceived = recv(sockfd, buffer, size, 0);
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

size_t SocketClient::receive(void *outData) {
    uint32_t length = 0;
    int code = recvData(&length, sizeof(uint32_t));
    if(code > 0){
        length = ntohl(length);
        recvData(outData, static_cast<size_t>(length));
    }
    return length;
}


void SocketClient::Close() {
    connected = false;
    if (sockfd > 0)
        close(sockfd);
}