#ifndef PASIVESERVER_H
#define PASIVESERVER_H
#include <server.h>

class pasiveServer: public server
{
public:
    pasiveServer(int connFd, int listenFd);
    void initialize();

protected:
    void syncServer();
};

#endif // PASIVESERVER_H
