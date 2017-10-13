#ifndef NODE_H
#define NODE_H
#include <rmref_h.h>

template <class T>
struct Node
{
public:
    Node();
    Node(char* key, T object, Node<T> *next);

    Node<T> *next;
    char* key;
    T object;
};

template <typename T>
Node<T>::Node(){}

template <typename T>
Node<T>::Node(char* key, T object, Node<T> *next){
    this->key = key;
    this->object = object;
    this->next = next;
}

#endif // NODE_H
