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

struct HTTP_Response
{
    HttpHeader header;
    std::string body;
};

enum HTTP_ContentTypes
{
    TEXT_HTML,
    IMG_PNG
};

enum HTTP_Status
{
    HTTP1_1_OK,
    HTTP1_1_404,
    HTTP1_1_302
};

enum HTTP_EncodingType
{
    HTTP_Encoding_None,
    HTTP_Encoding_Brotli,
    HTTP_Encoding_Deflate,
    HTTP_Encoding_Gzip
};

HttpHeader getDefaultHeader(HTTP_Status status, HTTP_ContentTypes type);
HttpHeader getRedirectHeader(const String &location);
HttpHeader get404Header();

void setStatus(HttpHeader & header, HTTP_Status status);
void addDate(HttpHeader & header);
void addContentLength(HttpHeader & header, size_t len);
void addContentType(HttpHeader & header, HTTP_ContentTypes type);
void addContentEncoding(HttpHeader & header, HTTP_EncodingType type);
void addLocation(HttpHeader & header, const String &uri);


std::ostream& operator << (std::ostream& stream, const HttpPair & pair);
std::ostream& operator << (std::ostream& stream, const HttpHeader & header);

#endif // HTTPHEADER_H
