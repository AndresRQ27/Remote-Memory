#ifndef RMLIB_H
#define RMLIB_H
#include <rmref_h.h>


class Rmlib
{

public:
    Rmlib();
    void rm_init (int ip, int port, int ipHA, int portHA);
    void rm_new (char* key, void* value, int value_size);
    rmRef_H rm_get(char* key);
    void rm_delete(rmRef_H* handler);

private:
    int *myServer;
    int server;
    int serverHA;
    int bufsize = 1024;
    char buffer[1024];
};

#endif // RMLIB_H
