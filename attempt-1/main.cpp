#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <arpa/inet.h>
#include <string>

#include "application.h"

using namespace std;

int main() {

    Application c = Application();
    Application s = Application();
    
    s.setPort(1234);
    c.setPort(1234);


    
    

    pid_t c_pid = fork();

    if (c_pid > 0) {// parent
        int sSock = s.listenForBind();

        
        while (1) {
            char buff[512] = { 0 };
            recv(sSock, buff, sizeof(buff), 0);
            cout << buff << endl;
            if (strcmp(buff, "exit") == 0) { break; }
        }
        close(sSock);
    }
    else {// child
        int cSock = c.bindTo("127.0.0.1", 1234);

        string msg;
        while (1) {
            cin >> msg;
            send(cSock, (const char*)msg.c_str(), strlen(msg.c_str()), 0);
            if (strcmp(msg.c_str(), "exit") == 0) { break; }
        }
        close(cSock);
    }
    



    return 0;

};