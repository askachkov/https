#include "client.h"
#include "utils.h"
#include "httpheader.h"
#include "http_request.h"
#include <iostream>
#include <sstream>

void processClient(SOCKET socket)
{
    int n;
    char buffer[1024];
    bzero(buffer,1024);
    n = recv(socket, buffer, 1024, 0);
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

    HttpHeader header = getDefaultHeader(HTTP1_1_OK, body.size(), TEXT_HTML);
    std::string message = toString(header) + body;

    //const char * resp = "HTTP/1.1 200 OK\nDate: Mon, 18 Feb 2019 10:02:37 GMT\nContent-Length: 4\nContent-Type: text/html\n\nText";
    n = send(socket, message.c_str(), message.size(), 0);
    if (n < 0)
        error("ERROR writing to socket");
#ifdef __WIN32__
    shutdown(socket, SD_SEND);
    closesocket(socket);
#endif// __WIN32__
}
