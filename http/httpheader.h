#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <string>
#include <vector>
#include <iostream>

typedef std::string String;

struct HttpPair
{
    String key;
    String value;
};

typedef std::vector<HttpPair> HttpPairs;

struct HttpHeader
{
    String statusLine;
    HttpPairs lines;
};

enum HTTP_ContentTypes
{
    TEXT_HTML
};

enum HTTP_Status
{
    HTTP1_1_OK
};

HttpHeader getDefaultHeader(HTTP_Status status, size_t len, HTTP_ContentTypes type);

std::ostream& operator << (std::ostream& stream, const HttpPair & pair);
std::ostream& operator << (std::ostream& stream, const HttpHeader & header);

#endif // HTTPHEADER_H
