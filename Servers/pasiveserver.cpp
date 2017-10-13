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
#include <thread>
#include "pasiveserver.h"

using namespace std;

pasiveServer::pasiveServer(int connFd, int listenFd):server::server(connFd, listenFd){}

void pasiveServer::initialize(){
    activeS = false;
    int portNum, serverFd, activeFd;
    char buffer[bufsize];
    string portNo, ip;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t len; //store size of the address

    cout << "Type the ip number of the active server: " << flush;
    getline(cin, ip);
    cout << "Type the port number of the active server: " << flush;
    getline(cin, portNo);
    portNum = stoi(portNo);

    if((portNum > 65535) || (portNum < 2000))
    {
        cerr << "=> Please enter a port number between 2000 - 65535" << endl;
        exit(1);
    }

    serverFd = socket(PF_INET, SOCK_STREAM, 0);

    if(serverFd < 0)
    {
        cerr << "=> Cannot open socket" << endl;
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNum);

    cout << "=> Connecting to active server..." << endl;

    //this is where client connects. svr will hang in this mode until client conn
    activeFd = connect(serverFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    *buffer = 'p';
    send(serverFd, buffer, bufsize, 0);

    if (activeFd < 0)
    {
        cerr << "=> Cannot accept connection" << endl;
        exit(1);
    }
    else
    {
        cout << "=> Connection successful" << endl;

        this->theOtherPort = portNum;
        serverSocket = serverFd;
        serverComm = activeFd;
        threadA[0] = std::thread(&server::communicationServer, this);
        threadA[0].detach();
    }

    cout << endl;

    int noThread = 1;
    while (noThread < 10)
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
            recv(connFd, buffer, bufsize, 0);
            cout << "=> Connection successful" << endl;
            //server::communicationClient(connFd, listenFd);
            threadA[noThread] = std::thread(&server::communicationClient, this, connFd, serverFd);
            threadA[noThread].detach();
            noThread++;
            }
        }
}

void pasiveServer::syncServer(){
    cout << "hello" << endl;
}
