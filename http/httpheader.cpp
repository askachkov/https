#include "httpheader.h"
#include <ctime>
#include "utils.h"

void setStatus(HttpHeader & header, HTTP_Status status)
{
    switch ( status ){
    case HTTP1_1_OK: header.statusLine = "HTTP/1.1 200 OK"; break;
    }
}

void addDate(HttpHeader & header)
{
    //Mon, 18 Feb 2019 10:02:37 GMT
    //Mon Oct  2 00:59:08 2017
    char mbstr[100];

    time_t rawtime;
    struct tm * ptm;
    time ( &rawtime );
    ptm = gmtime ( &rawtime );

    if (std::strftime(mbstr, sizeof(mbstr), "%a, %d %b %Y %H:%M:%S GMT", ptm)) {
        HttpPair date;
        date.key = "Date";
        date.value = mbstr;
        header.lines.push_back(date);
    }
}

void addContentLength(HttpHeader & header, size_t len)
{
    HttpPair pair;
    pair.key = "Content-Length";
    pair.value = toString(len);
    header.lines.push_back(pair);
}

void addContentType(HttpHeader & header, HTTP_ContentTypes type)
{
    HttpPair pair;
    pair.key = "Content-Type";
    switch ( type ){
    case TEXT_HTML: pair.value = "text/html"; break;
    }
    header.lines.push_back(pair);
}

std::ostream &operator <<(std::ostream &stream, const HttpPair &pair)
{
    return stream << pair.key << ": " << pair.value;
}

std::ostream &operator <<(std::ostream &stream, const HttpHeader &header)
{
    const char * end = "\n";
    stream << header.statusLine << end;
    for ( size_t i = 0; i < header.lines.size() && stream; ++i){
        stream << header.lines[i] << end;
    }
    return stream << end;
}

HttpHeader getDefaultHeader(HTTP_Status status, size_t len, HTTP_ContentTypes type)
{
    HttpHeader result;
    setStatus(result, status);
    addDate(result);
    addContentType(result, type);
    addContentLength(result, len);
    return result;
}
