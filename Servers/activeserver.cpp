#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <rmlib.h>
#include "activeserver.h"

using namespace std;

activeServer::activeServer(int connFd, int listenFd):server::server(connFd, listenFd){}

void activeServer::initialize(){
    struct sockaddr_in clientAddress;
    socklen_t len; //store size of the address

    for (int noThread = 1; noThread < 10; noThread++)
    {
        len = sizeof(clientAddress);
        listen(listenFd, 5);
        cout << "=> Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clientAddress, &len);

        if (connFd < 0)
        {
            cerr << "=> Cannot accept connection" << endl;
            exit(1);
        }
        else
        {
            char buffer[bufsize];
            recv(connFd, buffer, bufsize, 0);
            if (*buffer = 'p'){
                cout << "=> Connected to de pasive server" << endl;
                serverSocket = listenFd;
                serverComm = connFd;
                pthread_create(&threadA[0], NULL, communicationServer, NULL);
                pthread_join(threadA[0], NULL);
                cout << endl;
            } else {
                cout << "=> Connection successful" << endl;

                void *args = malloc(sizeof(int));
                args = &connFd;


                pthread_create(&threadA[noThread], NULL, communicationClient, args);
                pthread_join(threadA[noThread], NULL);
            }
        }
    }
}

void activeServer::syncServer(){
    cout << "hello" << endl;
}
