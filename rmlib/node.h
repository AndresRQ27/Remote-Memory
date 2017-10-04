#ifndef NODE_H
#define NODE_H
#include <rmref_h.h>

template <class T>
struct Node
{
public:
    Node();

    //Headers & Setters
    Node<T> *getNext() const;
    void setNext(Node<T> *value);

    T getObject() const;
    void setObject(const T &value);

    char *getKey() const;
    void setKey(char *value);

private:

    Node<T> *next;
    char* key;
    T object;
};

template <typename T>
Node<T>::Node(){}

template <typename T>
Node<T> *Node<T>::getNext() const
{
return this->next;
}

template <typename T>
void Node<T>::setNext(Node<T> *value)
{
this->next = value;
}

template <typename T>
T Node<T>::getObject() const
{
return this->object;
}

template <typename T>
void Node<T>::setObject(const T &value)
{
this->object = value;
}

template <typename T>
char *Node<T>::getKey() const
{
return key;
}

template <typename T>
void Node<T>::setKey(char *value)
{
key = value;
}

#endif // NODE_H
