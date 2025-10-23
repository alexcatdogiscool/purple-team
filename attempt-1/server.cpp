#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <arpa/inet.h>
#include <string>

#include "application.h"
#include "server.h"

using namespace std;

Server::Server() {}

void Server::protocol() {

    this->setPort(1234);

    string secret = "secret";

    int sSock = this->listenForBind();
    send(sSock, secret.c_str(), sizeof(secret.c_str()), 0);
    close(sSock);


}