#ifndef SOCKETSTREAM_H
#define SOCKETSTREAM_H

#include "socket.h"
#include <streambuf>
#include <iostream>

class SocketStream:
        public std::streambuf
{
public:
    SocketStream(const Socket & val = Socket());
    void closeSocket();
    int connect(const char * host, uint16_t portNo);

protected:
    int_type underflow();
    int_type overflow(int_type c);

private:
    Socket mSocket;
    const static int BUFFER_SIZE = 256;
    char mInputBuffer[BUFFER_SIZE];
    char mOutputBuffer[BUFFER_SIZE];
};

class ServerSocketStream
{
public:
    ServerSocketStream(uint16_t portNo);
    int bind();
    int listen(int n);
    SocketStream accept();
    void closeSocket();

private:
    Socket mSocket;
};

#endif // SOCKETSTREAM_H
