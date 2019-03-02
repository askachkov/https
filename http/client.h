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

void processClient(SOCKET socket, int logID);
void processClientSSL(SOCKET socket, int logID);

#endif // CLIENT_H
