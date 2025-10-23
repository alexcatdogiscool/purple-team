#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdint-uintn.h>
#include <arpa/inet.h>
#include <string>

#include "server.h"
#include "client.h"

using namespace std;

int main() {

    


    
    

    pid_t c_pid = fork();

    if (c_pid > 0) {// parent
        Server s = Server();
        s.protocol();
    }
    else {// child
        Client c = Client();
        c.protocol();
    }
    



    return 0;

};