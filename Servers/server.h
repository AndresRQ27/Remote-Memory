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
    int  serverSocket, serverComm, theOtherPort;
    int connFd, listenFd;
    static LinkedList<rmRef_H> list;
    const int bufsize = 1024;

    //Can't be static
    bool activeS;

    Node<rmRef_H> *cache[5];
    int counter;

    std::thread threadA[10];

    server(int connFd, int listenFd);

    virtual void initialize() = 0;

    void communicationClient(int const connFd, int const listenFd);
    void communicationServer();

    virtual void syncServer() = 0;

protected:

    void reconnect();
    string rmNew(int *connFd);
    string rmGet(int *connFd);
    string rmDelete(int *connFd);
    Node<rmRef_H> * findInCache(char *key);
};

#endif // SERVER_H
