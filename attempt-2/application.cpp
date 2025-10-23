#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <string>

#include "application.h"

using namespace std;

Application::Application() {
    primes = (int*)malloc(sizeof(int)*10);
    primes[0] = 11;
    primes[1] = 13;
    primes[2] = 17;
    primes[3] = 19;
    primes[4] = 23;
    primes[5] = 29;
    primes[6] = 31;
    primes[7] = 37;
    primes[8] = 41;
    primes[9] = 43;
}

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

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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


int Application::modInverse(int e, int phi) {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}


void Application::genKey(key& publicKey, key& secretKey) {
    int index1 = rand() % 10;
    int index2 = rand() % 10;
    while (index2 == index1) {
        index2 = rand() % 10;
    };
    int p = primes[index1];
    int q = primes[index2];

    int n = p*q;
    int phi_n = (p - 1)*(q - 1);

    int e;
    for (e = 2; e < n; e++) {
        if (__gcd(e, phi_n) == 1) {
            break;
        }
    }

    int d = modInverse(e, phi_n);

    key sk;
    secretKey.exponent = d;
    secretKey.modulus = n;

    key pk;
    publicKey.exponent = e;
    publicKey.modulus = n;

    
    
}


int Application::power(key k, int msg) {
    int res = 1;
    int base = msg;
    int m = k.modulus;
    int expo = k.exponent;

    base = base % m;
    while (expo > 0) {
        if (expo & 1)
            res = (res * 1LL * base) % m;
        base = (base * 1LL * base) % m;
        expo = expo / 2;
    }
    return res;
}


int Application::encrypt(key pk, int msg) {
    return power(pk, msg);
}

int Application::decrypt(key sk, int cipher) {
    return power(sk, cipher);
}


void Application::encryptStr(key k, string msg, cipherStr& c) {
    c.length = msg.length();
    c.cipher = (int*)malloc(sizeof(int)*msg.length());
    int i = 0;
    for (int i = 0; i < msg.length(); i++) {
        c.cipher[i] = encrypt(k, (int)msg[i]);
    };
}

char* Application::decryptStr(key k, cipherStr ciph, char* msg) {
    for (int i = 0; i < ciph.length; i++) {
        msg[i] = (char)decrypt(k, ciph.cipher[i]);
    }
    return msg;
}