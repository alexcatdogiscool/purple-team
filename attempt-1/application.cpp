#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <arpa/inet.h>

#include "application.h"

using namespace std;

Application::Application() {}

void Application::setPort(uint16_t p) {
    port = p;
}

uint16_t Application::getPort() {
    return port;
}

void Application::setIP(int a) {
    IP = a;
}

int Application::getIP() {
    return IP;
}


int Application::listenForBind() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 1);

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    return clientSocket;
}

int Application::bindTo(const char* dstAddr, uint16_t dstPort) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(dstPort);
    inet_pton(AF_INET, dstAddr, &serverAddress.sin_addr.s_addr);

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    return clientSocket;

}
