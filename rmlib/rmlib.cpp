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
#include <signal.h>

using namespace std;


Rmlib::Rmlib()
{
}

void Rmlib::rm_init (int ip, int port, int ipHA, int portHA){
    int socketServer, socketServerHA;
    struct sockaddr_in serverAddress, serverHAAddress;

    if(((port > 65535) || (port < 2000)) && ((portHA > 65535) || (portHA < 2000)))
    {
        cerr << "=> Please enter a port number between 2000 - 65535" << endl;
        exit(1);
    }

    server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverHA = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(server < 0 || serverHA < 0)
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

    socketServer = connect(server,(struct sockaddr *) &serverAddress, sizeof(serverAddress));
    socketServerHA = connect(serverHA,(struct sockaddr *) &serverHAAddress, sizeof(serverHAAddress));

    *buffer = 'c';
    send(server, buffer, bufsize, 0);
    send(serverHA, buffer, bufsize, 0);

    if (socketServer < 0 && socketServerHA < 0)
    {
        cout << "=> Connection Failed" << endl;
    } else {
        cout << "=> Connection to the server" << endl;
        cout << endl;
    }

    this->myServer = &server;
}

void Rmlib::rm_new (char* key, void* value, int value_size){
    *buffer = '1';
    send(*myServer, buffer, bufsize, 0);
    send(*myServer, key, bufsize, 0);
    send(*myServer, value, bufsize, 0);

    stringstream strs;
    strs << value_size;
    string temp_str = strs.str();
    char* size_char = (char*) temp_str.c_str();

    send(*myServer, size_char, bufsize, 0);

    char answer[bufsize];
    recv(*myServer, answer, bufsize, 0);
    cout << answer << endl;
}

rmRef_H Rmlib::rm_get(char* key){
    signal(SIGPIPE, SIG_IGN);
    try{
        *buffer = '2';
        send(*myServer, buffer, bufsize, 0);
        send(*myServer, key, bufsize, 0);

        char key2[bufsize];
        char value[bufsize];
        char value_size[bufsize];
        recv(*myServer, key2, bufsize, 0);
        recv(*myServer, value, bufsize, 0);
        recv(*myServer, value_size, bufsize, 0);

        rmRef_H object(&key2[0], (void *) value, stoi(value_size));

        char answer[bufsize];
        recv(*myServer, answer, bufsize, 0);
        cout << answer << endl;

        return object;
    } catch (exception e){
        rmRef_H object;
        cout << "=> Server down..." << endl;
        return object;
    }
}

void Rmlib::rm_delete(rmRef_H* handler){
    *buffer = '3';
    send(*myServer, buffer, bufsize, 0);
    send(*myServer, handler->key, bufsize, 0);

    char answer[bufsize];
    recv(*myServer, answer, bufsize, 0);
    cout << answer << endl;
}
