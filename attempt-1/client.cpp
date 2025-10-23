#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <arpa/inet.h>
#include <string>

#include "application.h"
#include "client.h"

using namespace std;

Client::Client() {}

void Client::protocol() {

    

    int cSock = this->bindTo("192.168.0.179", 1234);
    char buff[512] = { 0 };
    recv(cSock, buff, sizeof(buff), 0);
    cout << buff << endl;
    close(cSock);


}