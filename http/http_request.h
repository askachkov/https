#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "utils.h"
#include <vector>
#include <string>
#include <iostream>

typedef std::string String;

enum HTTP_Request_Type
{
    HTTP_Request_UNDEFINED,
    HTTP_Request_GET
};

typedef std::vector<String> StringList;

struct QuaryPair
{
    String key;
    String value;
};

typedef std::vector<QuaryPair> QuaryList;

struct HTTP_Request
{
    HTTP_Request_Type type;
    String host;
    uint16_t port;
    StringList path;
    QuaryList quary;
};

std::istream& operator>>(std::istream & stream, HTTP_Request & req);

#endif // HTTP_REQUEST_H
