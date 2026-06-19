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

    // hardcoded primes
    int p = 23;
    int g = 5;

    // chose a private prime
    int serverPrime = getRandPrime();

    // recv clients value
    int clientValue;
    recv(sSock, &clientValue, sizeof(int), 0);

    // generate and send value
    int val = power({p, serverPrime}, g);
    send(sSock, &val, sizeof(int), 0);

    // generate secret
    int secretKey = power({p, serverPrime}, clientValue);
    
    // recv cipher
    cipherStr ciph;
    recv(sSock, &ciph.length, sizeof(int), 0);
    ciph.cipher = (int*)malloc(sizeof(int)*ciph.length);
    recv(sSock, ciph.cipher, sizeof(int)*ciph.length, 0);

    // decrypt cipher
    char* msg = (char*)malloc(sizeof(char)*ciph.length);
    decryptStr(secretKey, ciph, msg);

    cout << "Server got: " << msg << endl;

    cout << "server secret prime: " << serverPrime << endl;
    cout << "server shared secret: " << secretKey << endl;

    close(sSock);


}