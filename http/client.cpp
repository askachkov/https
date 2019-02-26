#include "client.h"
#include "utils.h"
#include "httpheader.h"
#include "http_request.h"
#include <iostream>
#include <sstream>
#include "gzip.h"

struct IO
{
    virtual ~IO(){}
    virtual int read(char * buf, int size) = 0;
    virtual int write(const char * buf, int size) = 0;
};

struct PlainIO: IO
{
    SOCKET fd;
    int read(char * buf, int size)
    {
        return recv(fd, buf, size, 0);
    }
    int write(const char * buf, int size)
    {
        return send(fd, buf, size, 0);
    }
};

struct SSL_IO: IO
{
    SSL * ssl;
    int read(char * buf, int size)
    {
        return SSL_read(ssl, buf, size);
    }
    int write(const char * buf, int size)
    {
        return SSL_write(ssl, buf, size);
    }
};

void process(IO & io)
{
    int n;
    char buffer[1024];
    bzero(buffer,1024);
    //n = recv(socket, buffer, 1024, 0);
    n = io.read(buffer, 1024);
    if (n < 0)
        error("ERROR reading from socket");

    HTTP_Request req;
    std::istringstream iss(buffer);
    iss >> req;

    std::cout << "Request: " << buffer << std::endl << std::endl;

    std::string body("<PRE>");
    body+= buffer;
    body += '\n';
    body += '\n';
    for ( int i = 0; i < req.path.size(); ++i ){
        body += req.path[i] + ' ';
    }
    body += '\n';
    for ( int i = 0; i < req.quary.size(); ++i ){
        body += req.quary[i].key + '=' + req.quary[i].value + '\n';
    }
    body+= "</PRE>";

    std::cout << "Body: " << body.size() << std::endl << std::endl;
    body = Gzip::compress(body);

    std::cout << "ZBody: " << body.size() << std::endl << std::endl;

    HttpHeader header = getDefaultHeader(HTTP1_1_OK, body.size(), TEXT_HTML);
    std::string message = toString(header) + body;

    //const char * resp = "HTTP/1.1 200 OK\nDate: Mon, 18 Feb 2019 10:02:37 GMT\nContent-Length: 4\nContent-Type: text/html\n\nText";
    //n = send(socket, message.c_str(), message.size(), 0);
    n = io.write(message.c_str(), message.size());
    if (n < 0)
        error("ERROR writing to socket");
}

void processClient(SOCKET socket)
{
    PlainIO io;
    io.fd = socket;
    process(io);
    close(socket);
}

void processClientSSL(SOCKET socket)
{
    SSL_CTX* ctx;
    SSL*     ssl;
    const SSL_METHOD *meth;
    int err;

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();
    meth = SSLv23_server_method();
    ctx = SSL_CTX_new (meth);
    if (!ctx) {
      ERR_print_errors_fp(stderr);
      return;
    }

    if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0) {
      ERR_print_errors_fp(stderr);
      return;
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0) {
      ERR_print_errors_fp(stderr);
      return;
    }

    if (!SSL_CTX_check_private_key(ctx)) {
      fprintf(stderr,"Private key does not match the certificate public key\n");
      return;
    }

    ssl = SSL_new (ctx);
    if ((ssl)==NULL)
        return;
    SSL_set_fd (ssl, socket);
    err = SSL_accept (ssl);

    if ((err)==-1) {
        ERR_print_errors_fp(stderr);
        return;
    }

    SSL_IO io;
    io.ssl = ssl;
    process(io);
    close(socket);
}
