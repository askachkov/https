#include <iostream>
#include "socketstream.h"

using namespace std;

int main(int argc, char ** argv)
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif
    cout << "Starting... " << endl;
    ServerSocketStream server(1080);
    server.bind();
    server.listen(5);
    cout << "Listening... " << endl;
    SocketStream socket = server.accept();
    iostream ios(&socket);

    ios << 5;
    int x;
    ios >> x;

    cout << "Resp: " << x << endl;

    return 0;
}
