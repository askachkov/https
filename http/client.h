#ifndef CLIENT_H
#define CLIENT_H

extern "C" {

#ifdef __WIN32__
# include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

}


void processClient(SOCKET socket);

#endif // CLIENT_H
