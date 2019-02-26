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

/* define HOME to be dir for key and cert files... */
#define HOME "/home/as/QtProjects/keys/v1/"
/* Make these what you want for cert & key files */
#define CERTF  HOME "localhost.crt"
#define KEYF  HOME  "localhost.key"

#define CHK_NULL(x) if ((x)==NULL) return
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); return; }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); return; }

#include "client.h"


#include <openssl/rsa.h>       /* SSLeay stuff */
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

const int PORT_NO = 2080;
const int PORT_SSL_NO = 2443;

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
