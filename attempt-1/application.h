#pragma once
#include <bits/stdint-uintn.h>



class Application {
public:

    Application();
    //~Application();

    void setPort(uint16_t p);
    void setIP(int a);

    uint16_t getPort();
    int getIP();

    int listenForBind();
    int bindTo(const char* addr, uint16_t port);

    //char* recvMsg(int sock);



private:
    uint16_t port;
    int IP;
};