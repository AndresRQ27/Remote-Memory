#include <iostream>
#include <linkedlist.h>
#include <node.h>
#include <rmlib.h>
#include <rmref_h.h>

using namespace std;

static LinkedList<rmRef_H> list;

void rminit();
void rmNew();
void rmGet();
void rmDelete();
void signal1(char *key, void* value, int value_size);
void signal2(char *key);
void signal3(rmRef_H *object);

static Rmlib rmlib;

int main()
{
    cout << "Hello World!" << endl;
    rminit();
    string command;
    while (true) {
        cout << "Enter your next action: (1)rm_new, (2)rm_get, (3)rm_delete" << endl;
        cin >> command;
        switch (stoi(command)) {
        case 1:{
            rmNew();
            break;
        }
        case 2:{
            rmGet();
            break;
        }
        case 3:{
            rmDelete();
            break;
        }
        default:
            cout << "Commando incorrecto" << flush;
            break;
        }
    }
    return 0;
}

void rminit(){
    string ip, port, ipHA, portHA;
    cout << "Please enter the ip and port of the main server and it's backup :)" << endl;
    cout << "=> ip: " << flush;
    getline(cin, ip);
    cout << "=> port: " << flush;
    getline(cin, port);
    cout << "=> ipHA: " << flush;
    getline(cin, ipHA);
    cout << "=> portHA: " << flush;
    getline(cin, portHA);

    rmlib.rm_init(stoi(ip), stoi(port), stoi(ipHA), stoi(portHA));
}

void rmNew(){
    char *key = new char[1024];
    char *value = new char[1024];
    char value_size[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;
    cout << "=> value: " << flush;
    cin >> value;
    cout << "=> value_size: " << flush;
    cin >> value_size;
    cout << endl;

    rmlib.rm_new(&key[0], (void*) &value[0], atoi(value_size));
    signal1(key, value, atoi(value_size));
}

void rmGet(){
    char key[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;
    cout << endl;

    try{
        rmRef_H object = rmlib.rm_get(&key[0]);
        cout << "Key: " << object.key << endl;
        cout << "Value: " << object.value << endl;
        cout << "Value_Size: " << object.value_size << endl;

    } catch (exception e){

        signal2(&key[0]);
    }
        cout << endl;

}

void rmDelete(){
    char key[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;
    cout << endl;
    rmRef_H object(&key[0], NULL, 0);
    rmlib.rm_delete(&object);
    signal3(&object);
}









void signal1(char *key, void* value, int value_size){
    rmRef_H object(key, value, value_size);
    list.addNode(object, key);
}

void signal2(char *key){
    Node<rmRef_H> *objectP = list.search(key);
    cout << "Key: " << objectP->object.key << endl;
    cout << "Value: " << (char *) objectP->object.value << endl;
    cout << "Value_Size: " << objectP->object.value_size << endl;
}

void signal3(rmRef_H *object){
    Node<rmRef_H> *objectP = list.removeNode(object->key);
    delete(objectP->object.key);
    delete(objectP->object.value);
    delete(objectP);
}
