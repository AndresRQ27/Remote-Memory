#include <iostream>
#include <rmlib.h>

using namespace std;

void rminit();
void rmNew();
void rmGet();
void rmDelete();

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
    char key[1024], value[1024], value_size[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;
    cout << "=> value: " << flush;
    cin >> value;
    cout << "=> value_size: " << flush;
    cin >> value_size;

    rmlib.rm_new(&key[0], (void*) &value[0], atoi(value_size));
}

void rmGet(){
    char key[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;

    rmlib.rm_get(&key[0]);
}

void rmDelete(){
    char key[1024];
    cout << "Please enter the needed information" << endl;
    cout << "=> key: " << flush;
    cin >> key;
    rmRef_H object(&key[0], NULL, 0);
    rmlib.rm_delete(&object);
}
