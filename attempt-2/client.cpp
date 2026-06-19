#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <string>
#include <cstdlib>

#include "application.h"
#include "client.h"

using namespace std;

Client::Client() {}

void Client::protocol() {

    string secret;;
    cin >> secret;

    int cSock = this->bindTo("192.168.0.111", 1234);
    key serverKey;
    // recv public key
    recv(cSock, &serverKey.modulus, sizeof(serverKey.modulus), 0);
    recv(cSock, &serverKey.exponent, sizeof(serverKey.exponent), 0);
    
    // encrypt message
    cipherStr ciph;
    encryptStr(serverKey, secret, ciph);

    // send cipher and its length
    send(cSock, &ciph.length, sizeof(int), 0);
    send(cSock, ciph.cipher, sizeof(int)*ciph.length, 0);
    
    close(cSock);


}