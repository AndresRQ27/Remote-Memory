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
#include <signal.h>
#include "server.h"

using namespace std;

server::server(int connFd, int listenFd)
{
    this->connFd = connFd;
    this->listenFd = listenFd;
    counter = 0;
}

void server::communicationServer(){
    while (true) {
        char read[bufsize] = {0};
        recv(serverSocket, read, bufsize, 0);
        switch (atoi(read)) {
            case 1:{
                rmNew(&serverSocket);
                break;
            }
            case 2:{
                rmGet(&serverSocket);
                break;
            }
            case 3:{
                rmDelete(&serverSocket);
                break;
            }
            default:{
                break;
            }
        }
    }
}

void server::communicationClient(int connFd, int listenFd){
    signal(SIGPIPE, SIG_IGN);
    //std::thread recovery;
    try{
        char read[bufsize] = {0};
        while (true) {
            recv(connFd, read, bufsize, 0);

            if (activeS){
                send(serverComm, read, bufsize, 0);
            } else {
                //recovery = std::thread(&server::reconnect, this);
                //recovery.detach();
                reconnect();
            }

            string answer;
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
            if (answer != ""){
                send(connFd, answer.c_str(), bufsize, 0);
            } else {
                answer = "=> Operation invalid";
                send(connFd, answer.c_str(), bufsize, 0);
            }

        }
    } catch (...){
        cout << "=> Client lost..." << endl;
        //Close thread
    }
}

string server::rmNew(int *connFd){
    char * key = new char[bufsize]();
    char * value = new char[bufsize]();
    char value_size[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);
    recv(*connFd, value, bufsize, 0);
    recv(*connFd, value_size, bufsize, 0);

    if (activeS){
        send(serverComm, key, bufsize, 0);
        send(serverComm, value, bufsize, 0);
        send(serverComm, value_size, bufsize, 0);
    }

    rmRef_H newRm(key, value, atoi(value_size));

    string answer;

    if(!list.addNode(newRm, key)){
        answer = "=> Error creating the node. Is the key already in?";
    } else {
        answer = "=> Node created";
        cache[counter] = list.head;
        counter++;
        if (counter >= 5){
            counter = 0;
        }
    }

    return answer;
}

string server::rmGet(int *connFd){
    char key[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);

    Node<rmRef_H> * object;

    object = findInCache(key);
    if(object == NULL){
        object = list.search(key);
        cache[counter] = object;
        counter++;
        if (this->counter >= 5){
            this->counter = 0;
        }
    }

    int number = object->object.value_size;
    std::string s = std::to_string(number);

    send(*connFd, object->object.key, bufsize, 0);
    char *laVoide = (char *) object->object.value;
    send(*connFd, laVoide, bufsize, 0);
    send(*connFd, s.c_str(), bufsize, 0);

    string answer;
    if(object == NULL){
        answer = "=> Error finding the node. Does it exist?";
    } else {
        answer = "=> Node found";
    }

    return answer;
}

string server::rmDelete(int *connFd){
    char key[bufsize] = {0};
    recv(*connFd, key, bufsize, 0);

    if (activeS){
        send(serverComm, key, bufsize, 0);
    }

    Node<rmRef_H> * object = list.removeNode(key);

    string answer;
    if(object == NULL){
        answer = "=> Node cant be deleted. Does it exist?";
    } else {
        delete(object->object.key);
        delete(object->object.value);
        delete(object);
        answer = "=> Node deleted";
    }
    return answer;
}

Node<rmRef_H> * server::findInCache(char *key){
    int i = 0;
    if(list.length > 0){
        string searchKey;
        string wholeKey = key;

        int cached;
        if (list.length < 5){
            cached = list.length;
        } else {
            cached = 5;
        }

        for(;i < cached; i++){
            searchKey = cache[i]->key;
            if (searchKey == wholeKey){
                break;
            }
        }
    }
    return cache[i];
}

void server::reconnect(){
    try{
        struct sockaddr_in serverAddress;

        serverSocket = socket(PF_INET, SOCK_STREAM, 0);

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(this->theOtherPort);

        serverComm = connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
        if(!(serverComm < 0)){
            char buffer = 'p';
            send(serverSocket, &buffer, bufsize, 0);
        }
    } catch (...){}
}

LinkedList<rmRef_H> server::list = LinkedList<rmRef_H>();
