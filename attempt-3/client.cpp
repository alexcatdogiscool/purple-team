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

    cout << "write your secret message: ";

    string secret;;
    cin >> secret;

    cout << endl;

    int cSock = this->bindTo("192.168.0.111", 1234);
    

    // hardcoded public primes
    int p = 23;
    int g = 5;

    // chose a private prime
    int clientPrime = getRandPrime();

    // generate and send value
    int val = power({p, clientPrime}, g);
    send(cSock, &val, sizeof(int), 0);

    // recv servers value
    int serverValue;
    recv(cSock, &serverValue, sizeof(int), 0);

    // generate secret
    int secretKey = power({p, clientPrime}, serverValue);
    
    // encrypt message
    cipherStr ciph;
    encryptStr(secretKey, secret, ciph);

    // send cipher and its length
    send(cSock, &ciph.length, sizeof(int), 0);
    send(cSock, ciph.cipher, sizeof(int)*ciph.length, 0);
    
    cout << "Client secret prime: " << clientPrime << endl;
    cout << "client shared secret: " << secretKey << endl;

    close(cSock);


}