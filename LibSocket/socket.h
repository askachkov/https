#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>
#ifdef __WIN32__

class WA_Service
{
    WA_Service(const WA_Service&) = delete;
    WA_Service & operator=(const WA_Service&) = delete;
    WA_Service();
    static WA_Service * INSTANCE;
public:
    static WA_Service * instance();
};

# include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

class Socket
{
public:
    Socket(int socketFD, struct sockaddr_in & addr);
    Socket(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    void setAddr(struct sockaddr_in addr);
    sockaddr_in getAddr()const;
    int read(uint8_t * buf, uint32_t maxSize);
    int write(uint8_t * buf, uint32_t size);
    void close();
    int connect(const char * host, uint16_t portNo);
    void setPort(uint16_t portNo);
    int bind();
    int listen(int n);
    Socket accept();

protected:
    int getSockFD()const;

private:
    struct sockaddr_in mAddr;
    int mSockFD;
};

#endif // SOCKET_H
