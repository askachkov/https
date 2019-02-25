#ifndef UTILS_H
#define UTILS_H

#include <sstream>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __WIN32__
# include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

}
#include "client.h"


const int PORT_NO = 1080;

void error(const char *msg);
void bzero(void * ptr, size_t size);


template <typename T>
std::string toString(const T & val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *urlEncode(const char *str);

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
std::string urlDecode(const std::string &str);


#endif // UTILS_H
