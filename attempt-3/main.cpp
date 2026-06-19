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
//#include "attacker.h"

using namespace std;

int main() {

    


    
    

    pid_t c_pid = fork();

    if (c_pid > 0) {// parent

        //pid_t c_pid2 = fork();

        //if (c_pid2 > 0) {
        //    Attacker a = Attacker();
        //    a.protocol();
        //}
        if (1 == 0) {}
        else { 
            Server s = Server();
            s.protocol();
            
        }

        
    }
    else {// child
        Client c = Client();
        c.protocol();
    }
    



    return 0;

};