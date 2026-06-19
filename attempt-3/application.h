#pragma once
#include <bits/stdint-uintn.h>
#include <string>

using namespace std;

struct key {
    int modulus;
    int exponent;
} typedef key;

struct cipherStr {
    int* cipher;
    int length;
} typedef cipherStr;

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

    void genKey(key& pk, key&sk);
    int getRandPrime();
    int modInverse(int e, int phi);
    int power(key k, int m);
    int encrypt(int pk, int msg);
    int decrypt(int sk, int cipher);
    void encryptStr(int k, string msg, cipherStr& ciph);
    char* decryptStr(int k, cipherStr ciph, char* msg);
    

    //char* recvMsg(int sock);

    int* primes;

private:
    uint16_t port;
    int IP;
    
};


