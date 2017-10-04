#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <node.h>

template <typename T>
struct LinkedList
{
public:
    Node<T> *head;
    unsigned int length;

    LinkedList();

    bool addNode(T object, char *key);

    bool removeNode(char* key);

    T getNode(char* key);

    bool search(char* key);
};

template <typename T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->length = 0;
}

template <typename T>
bool LinkedList<T>::search(char *key){
    Node<T> *aux = this->head;
    bool flag = false;
    for(int i = 0; i < this->length; i++){
        if (*aux->getKey() = *key){
            flag = true;
        }
    }
    return flag;
}

template <typename T>
bool LinkedList<T>::addNode(T object, char *key){
    bool flag = true;
    if (search(key) && length > 0){
        flag = false;
    } else {
        Node<T>* newNode = new Node<T>();
        //IMPLEMENTAR DEEP COPY POR SI LLEGA HABER ALGÚN PROBLEMA
        newNode->setKey(key);
        newNode->setObject(object);
        newNode->setNext(this->head);
        this->head = newNode;
        this->length += 1;
    }
    return flag;
}

template <typename T>
bool LinkedList<T>::removeNode(char* key){
    bool flag = true;
    if(search(key)){
        Node<T> *aux = this->head;
        for(int i = 0; i < this->length; i++){
            if (*aux->getNext()->getKey() = key){
                Node<T> *deleteThis = aux->getNext();
                aux->setNext(deleteThis->getNext());
                delete deleteThis;
                this->length -= 1;
            }
        }
    } else {
        flag = false;
    }
    return flag;
}

#endif // LINKEDLIST_H
