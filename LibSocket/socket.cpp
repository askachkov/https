#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

void error(const char *msg)
{
    perror(msg);
    //exit(1);
}

Socket::Socket(int af, int type, int protocol)
{
#ifdef __WIN32__
    WA_Service::instance();
#endif
    memset(&mAddr, 0, sizeof(mAddr));
    mSockFD = static_cast<int>( socket(static_cast<short>(af), type, protocol));
    if (mSockFD < 0)
        error("ERROR opening socket");
}

void Socket::setAddr(struct sockaddr_in addr)
{
    mAddr = addr;
}

sockaddr_in Socket::getAddr() const
{
    return mAddr;
}

int Socket::read(uint8_t *buf, uint32_t maxSize)
{
    return ::read(mSockFD,buf,maxSize);
}

int Socket::write(uint8_t *buf, uint32_t size)
{
    return ::write(mSockFD,buf,size);
}

void Socket::close()
{
    if ( mSockFD >= 0 )
        ::close(mSockFD);
}

Socket::Socket(int socketFD, sockaddr_in &addr)
{
#ifdef __WIN32__
    WA_Service::instance();
#endif
    mSockFD = socketFD;
    mAddr = addr;
}

int Socket::getSockFD() const
{
    return mSockFD;
}

int Socket::bind()
{
    sockaddr_in addr = getAddr();
    return ::bind(static_cast<SOCKET>(getSockFD()), reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
}

int Socket::listen(int n)
{
    return ::listen(static_cast<SOCKET>(getSockFD()), n);
}

Socket Socket::accept()
{
    sockaddr_in addr;
    int clilen = sizeof(addr);
    memset(&addr, 0, sizeof(addr));
    SOCKET newsockfd = ::accept(static_cast<SOCKET>(getSockFD()), reinterpret_cast<struct sockaddr *>(&addr), &clilen);
    return Socket(static_cast<int>(newsockfd), addr);
}

#ifdef __WIN32__

WA_Service * WA_Service::INSTANCE = nullptr;

WA_Service::WA_Service()
{
   WORD versionWanted = MAKEWORD(1, 1);
   WSADATA wsaData;
   WSAStartup(versionWanted, &wsaData);
}

WA_Service *WA_Service::instance()
{
    if ( INSTANCE == nullptr ){
        INSTANCE = new WA_Service();
    }
    return INSTANCE;
}
#endif

int Socket::connect(const char *host, uint16_t portNo)
{
    struct hostent *server;
    server = gethostbyname(host);
    if (server == nullptr) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    sockaddr_in addr = getAddr();
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr.s_addr, server->h_addr, static_cast<size_t>(server->h_length));
    addr.sin_port = htons(portNo);
    return ::connect(static_cast<SOCKET>(getSockFD()),reinterpret_cast<struct sockaddr *>( &addr ),sizeof(addr));
}

void Socket::setPort(uint16_t portNo)
{
    mAddr.sin_family = AF_INET;
    mAddr.sin_addr.s_addr = INADDR_ANY;
    mAddr.sin_port = htons(portNo);
}
