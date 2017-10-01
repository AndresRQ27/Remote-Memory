#include <iostream>
#include <rmlib.h>

using namespace std;

int main()
{
    string ip, port, ipHA, portHA;
    cout << "Hello World!" << endl;
    cout << "Please enter the ip and port of the main server and it's backup :)" << endl;
    cout << "=> ip: " << flush;
    getline(cin, ip);
    cout << "=> port: " << flush;
    getline(cin, port);
    cout << "=> ipHA: " << flush;
    getline(cin, ipHA);
    cout << "=> portHA: " << flush;
    getline(cin, portHA);

    Rmlib rmlib;
    rmlib.rm_init(stoi(ip), stoi(port), stoi(ipHA), stoi(portHA));
    return 0;
}
