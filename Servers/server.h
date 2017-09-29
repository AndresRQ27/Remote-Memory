#ifndef SERVER_H
#define SERVER_H
#include <pthread.h>


class server
{
public:
    int connFd, listenFd;
    int bufsize = 1024;
    pthread_t threadA[10];

    server(int connFd, int listenFd);

    virtual void initialize() = 0;

protected:

    static void * communicationClient(void *pointer);
    static void * communicationServer(void *pointer);

    virtual void syncServer() = 0;
};

#endif // SERVER_H
