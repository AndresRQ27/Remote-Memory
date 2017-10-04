#ifndef RMLIB_H
#define RMLIB_H
#include <rmref_h.h>


class Rmlib
{

public:
    Rmlib();
    void rm_init (const int ip, const int port, const int ipHA, const int portHA);
    void rm_new (char* const key, void* const value, const int value_size);
    rmRef_H rm_get(char* const key);
    void rm_delete(rmRef_H* const handler);

private:
    int *myServer;
    int server;
    int serverHA;
    int bufsize = 1024;
    char buffer[1024];
};

#endif // RMLIB_H
