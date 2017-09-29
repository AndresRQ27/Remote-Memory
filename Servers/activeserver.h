#ifndef ACTIVESERVER_H
#define ACTIVESERVER_H
#include <server.h>

class activeServer: public server
{
public:
    activeServer(int connFd, int listenFd);
    void initialize();

protected:
    void syncServer();
};

#endif // ACTIVESERVER_H
