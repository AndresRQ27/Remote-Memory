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
    while (true) {
        char read[bufsize] = {0};
        recv(connFd, read, bufsize, 0);
        switch (atoi(read)) {
            case 1:{
                const char * buffer = rmNew(&connFd);
                send(connFd, buffer, bufsize, 0);
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
}

void server::communicationClient(int connFd, int listenFd){
    try{
        char read[bufsize];
        char null[bufsize] = {0};
        while (true) {
            recv(connFd, read, bufsize, 0);
            const char *answer = &null[0];
            switch (atoi(read)) {
                case 1:{
                    answer = rmNew(&connFd);
                    break;
                }
                case 2:{
                    answer = rmGet(&connFd);
                    break;
                }
                case 3:{
                    answer = rmDelete(&connFd);
                    break;
                }
                default:{
                    break;
                }
            }
            send(connFd, answer, bufsize, 0);
        }
    } catch (exception e){
        cout << "=> Client lost..." << endl;
    }
}

const char * server::rmNew(int *connFd){
    char * key = new char[bufsize]();
    char * value = new char[bufsize]();
    char value_size[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);
    recv(*connFd, value, bufsize, 0);
    recv(*connFd, value_size, bufsize, 0);
    rmRef_H newRm(key, value, atoi(value_size));

    string answer = "";

    if(!list.addNode(newRm, key)){
        answer = "=> Error creating the node. Is the key already in?";
    } else {
        answer = "=> Node created";
    }

    return answer.c_str();
}

const char * server::rmGet(int *connFd){
    char key[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);
    Node<rmRef_H> * object = list.search(key);

    int number = object->object.value_size;
    std::string s = std::to_string(number);

    send(*connFd, object->object.key, bufsize, 0);
    send(*connFd, object->object.value, bufsize, 0);
    send(*connFd, s.c_str(), bufsize, 0);

    string answer = "";
    if(object == NULL){
        answer = "=> Error finding the node. Does it exist?";
    } else {
        answer = "=> Node found";
    }

    return answer.c_str();
}

const char * server::rmDelete(int *connFd){
    char key[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);

    Node<rmRef_H> * object = list.removeNode(key);

    string answer = "";
    if(object == NULL){
        answer = "=> Node can't be deleted. Does it exist?";
    } else {
        free(object->object.key);
        free(object->object.value);
        free(object);
        answer = "=> Node deleted";
    }
    return answer.c_str();
}

LinkedList<rmRef_H> server::list = LinkedList<rmRef_H>();
