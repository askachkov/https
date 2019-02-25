#include <iostream>
#include "socketstream.h"

using namespace std;

int main(int argc, char ** argv)
{
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);

    SocketStream client;
    client.connect("127.0.0.1", 1080);
    iostream ios(&client);

    int x;
    ios >> x;
    cout << "Server: " << x << endl;
    ios << 33;

    return 0;
}
