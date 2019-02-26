#ifndef CLIENT_H
#define CLIENT_H

extern "C" {

#ifdef __WIN32__
# include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#define SOCKET int

#endif

}

void processClient(SOCKET socket);
void processClientSSL(SOCKET socket);

#endif // CLIENT_H
