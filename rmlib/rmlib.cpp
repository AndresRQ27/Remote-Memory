#include <rmlib.h>
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

using namespace std;


Rmlib::Rmlib()
{
}

void Rmlib::rm_init (int ip, int port, int ipHA, int portHA){
    int socketServer, socketServerHA;
    struct sockaddr_in serverHAAddress, serverAddress;
    //socklen_t len; //store size of the address

    if((port > 65535) || (port < 2000))
    {
        cerr << "=> Please enter a port number between 2000 - 65535" << endl;
        exit(1);
    }

    socketServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    socketServerHA = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketServer < 0)
    {
        cout << "\n=>Error establishing socket..." << endl;
    }

    cout << "\n=> Socket client has been created..." << endl;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    serverHAAddress.sin_family = AF_INET;
    serverHAAddress.sin_addr.s_addr = INADDR_ANY;
    serverHAAddress.sin_port = htons(portHA);

    server = connect(socketServer,(struct sockaddr *) &serverAddress, sizeof(serverAddress));
    serverHA = connect(socketServerHA,(struct sockaddr *) &serverHAAddress, sizeof(serverHAAddress));

    *buffer = 'c';
    send(socketServer, buffer, bufsize, 0);
    send(socketServerHA, buffer, bufsize, 0);

    if (server < 0 && serverHA < 0)
    {
        cout << "=> Connection Failed" << endl;
    } else {
        cout << "=> Connection to the active server" << endl;
    }

    this->myServer = &server;
}

void Rmlib::rm_new (char* key, void* value, int value_size){

}

rmRef_H Rmlib::rm_get(char* key){
    *buffer = 'get';
    send(*myServer, buffer, bufsize, 0);
    send(*myServer, key, bufsize, 0);
}

void Rmlib::rm_delete(rmRef_H* handler){

}
