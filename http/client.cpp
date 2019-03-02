#include "client.h"
#include "utils.h"
#include "httpheader.h"
#include "http_request.h"
#include <iostream>
#include <sstream>
#include <map>
#include <cgzip/gzip.h>
#include "handlers.h"

std::map<std::string, Handler> MAP = {
    std::make_pair("/help", helpHandler), //Help handler
    //std::make_pair("/file", fileHandler), //Help handler
    std::make_pair("/index.htm", indexHandler), //Help handler
    std::make_pair("/", redirectToIndexHandler), //Help handler
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
    n = io.read(buffer, 1024);
    if (n < 0){
        error("ERROR reading from socket");
        return;
    }
    std::cout << "Request: " << buffer << std::endl << std::endl;
    HTTP_Request req;
    std::istringstream iss(buffer);
    iss >> req;

    std::string message;
    HTTP_Response resp;
    if ( MAP.find(req.path) != MAP.end() ){
        resp = MAP[req.path](req);
    } else {
        //message = toString( getDefaultHeader(HTTP1_1_404, 0, TEXT_HTML) );
        resp = fileHandler(req);
    }

    if ( !resp.body.empty() )
        resp.body = Gzip::compress(resp.body);
    addContentLength(resp.header, resp.body.size());
    message = toString(resp.header) + resp.body;

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
