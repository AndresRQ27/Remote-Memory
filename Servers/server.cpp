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
#include "server.h"

using namespace std;

server::server(int connFd, int listenFd)
{
    this->connFd = connFd;
    this->listenFd = listenFd;
}

void server::communicationServer(int connFd, int listenFd){
    task1(NULL);
}

void server::communicationClient(int connFd, int listenFd){
    try{
        char read[bufsize];
        while (true) {
            recv(connFd, read, bufsize, 0);
            cout << "señal de vida" << endl;
            switch (atoi(read)) {
                case 1:{
                    rmNew(&connFd);
                    cout << "señal de vida 2" << endl;
                    break;
                }
                case 2:{

                    break;
                }
                case 3:{

                    break;
                }
                default:{
                    break;
                }
            }
        }
    } catch (exception e){
        cout << "=> Client lost..." << endl;
    }
    task1(NULL);
}

void server::rmNew(int *connFd){
    char *key;
    char *value;
    char *value_size;
    recv(*connFd, key, bufsize, 0);
    recv(*connFd, value, bufsize, 0);
    recv(*connFd, value_size, bufsize, 0);
    rmRef_H newRm(key, (void *) value, atoi(value_size));
    list.addNode(newRm, key);
}

void * server::task1 (void *dummyPt)
{
    int i = 0;
    cout << "Thread No: " << i << endl;
    return NULL;
}

//std::thread * server::threadA[] = std::thread[10];

LinkedList<rmRef_H> server::list = LinkedList<rmRef_H>();
