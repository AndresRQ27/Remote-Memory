#include "server.h"

server::server(int connFd, int listenFd)
{
    this->connFd = connFd;
    this->listenFd = listenFd;
}

void * server::communicationServer(void *pointer){

}

void * server::communicationClient(void *pointer){

}
