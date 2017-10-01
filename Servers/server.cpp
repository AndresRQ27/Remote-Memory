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

void * server::communicationServer(void *pointer){
    task1(pointer);
    return NULL;
}

void * server::communicationClient(void *pointer){
    task1(pointer);
    return NULL;
}

void * server::task1 (void *dummyPt)
{
    cout << "Thread No: " << pthread_self() << endl;
    return NULL;
}
