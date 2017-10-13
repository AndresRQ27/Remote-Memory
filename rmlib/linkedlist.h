#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <node.h>

using namespace std;

template <typename T>
struct LinkedList
{
public:
    Node<T> *head;
    unsigned int length;

    LinkedList();

    bool addNode(T object, char *key);

    Node<T> * removeNode(char* key);

    Node<T> * search(char* key);
};

template <typename T>
LinkedList<T>::LinkedList(){
    this->head = NULL;
    this->length = 0;
}

template <typename T>
Node<T> * LinkedList<T>::search(char *key){
    Node<T> *aux = this->head;
    if(length > 0){
        string searchKey;
        string wholeKey = key;
        for(int i = 0; i < this->length; i++){
            searchKey = aux->key;
            if (searchKey == wholeKey){
                break;
            } else {
                aux = aux->next;
            }
        }
    }
    return aux;
}

template <typename T>
bool LinkedList<T>::addNode(T object, char *key){
    bool flag = true;
    if (search(key) != NULL){
        flag = false;
    } else {
        Node<T>* newNode = new Node<T>(key, object, this->head);
        //IMPLEMENTAR DEEP COPY POR SI LLEGA HABER ALGÚN PROBLEMA
        this->head = newNode;
        this->length += 1;
    }
    return flag;
}

template <typename T>
Node<T> * LinkedList<T>::removeNode(char* key){
    Node<T> *deleteThis = NULL;
    string wholeKey = key;
    string searchKey;
    if(search(key) != NULL){
        Node<T> *aux1 = this->head;
        Node<T> *aux2 = this->head;
        for(int i = 0; i < this->length; i++){
            searchKey = aux1->key;
            if (searchKey == wholeKey){
                deleteThis = aux1;
                aux2->next = deleteThis->next;
                this->length -= 1;
                if (aux1 == aux2){
                    this->head = aux1->next;
                }
                break;
            } else {
                aux2 = aux1;
                aux1 = aux1->next;
            }
        }
    }
    return deleteThis;
}

#endif // LINKEDLIST_H
