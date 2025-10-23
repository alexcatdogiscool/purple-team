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

    key pk;
    key sk;
    genKey(pk, sk);

    int sSock = this->listenForBind();

    // send public key
    send(sSock, &pk.modulus, sizeof(pk.modulus), 0);
    send(sSock, &pk.exponent, sizeof(pk.exponent), 0);
    
    // recv cipher
    cipherStr ciph;
    recv(sSock, &ciph.length, sizeof(int), 0);
    ciph.cipher = (int*)malloc(sizeof(int)*ciph.length);
    recv(sSock, ciph.cipher, sizeof(int)*ciph.length, 0);

    // decrypt cipher
    char* msg = (char*)malloc(sizeof(char)*ciph.length);
    decryptStr(sk, ciph, msg);

    cout << msg << endl;
    

    close(sSock);


}