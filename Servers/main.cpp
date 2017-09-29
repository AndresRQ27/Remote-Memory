#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <server.h>
#include <pasiveserver.h>
#include <activeserver.h>

using namespace std;

int main()
{
    int listenFd, portNum, connFd;
    string portNo;
    struct sockaddr_in serverAddress;

    cout << "Type the port number: " << flush;
    getline(cin, portNo);
    portNum = stoi(portNo);

    if((portNum > 65535) || (portNum < 2000))
    {
        cerr << "=> Please enter a port number between 2000 - 65535" << endl;
        exit(1);
    }


    //create socket
    listenFd = socket(PF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        cerr << "=> Cannot open socket" << endl;
        exit(1);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(portNum);

    //bind socket
    if(bind(listenFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "=> Cannot bind" << endl;
        exit(1);
    }

    string serverType;
    while (true) {
        cout << "Type the kind of server you want:" << endl;
        cout << endl << "\'active\' for an active type server" << endl;
        cout << "\'pasive\' for a pasive type server" << endl;
        cout << "=> " << flush;
        getline(cin, serverType);
        cout << endl;

        if (serverType == "active"){
            activeServer server(connFd, listenFd);
            server.initialize();
            break;
        } else if (serverType == "pasive"){
            pasiveServer server(connFd, listenFd);
            server.initialize();
        } else {
            cerr << "=> Error in the type of the server" << endl;
        }
    }
}
