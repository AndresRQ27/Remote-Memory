#ifndef SERVER_H
#define SERVER_H
#include <pthread.h>
#include <node.h>
#include <linkedlist.h>
#include <rmref_h.h>
#include <thread>


class server
{
public:
    int  serverSocket, serverComm;
    int connFd, listenFd;
    static LinkedList<rmRef_H> list;
    const int bufsize = 1024;

    std::thread threadA[10];

    server(int connFd, int listenFd);

    virtual void initialize() = 0;

    void communicationClient(int const connFd, int const listenFd);
    void communicationServer(int const connFd, int const listenFd);
    static void *task1(void *);

    virtual void syncServer() = 0;

protected:

    void rmNew(int *connFd);
};

#endif // SERVER_H
