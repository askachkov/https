#include "http_request.h"
#include "utils.h"

//GET /weerer HTTP/1.1
//Host: localhost:1080
//User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
//Accept-Language: ru-RU,ru;q=0.8,en-

void readPath(std::istream &stream, HTTP_Request &req)
{
    String buffer;
    char ch;
    while ( stream.peek() == ' ' ){
        stream.get(ch);
    }
    while ( stream.get(ch) ){
        if ( ch == '?' || ch == ' ' ){
            stream.putback(ch);
            if ( !buffer.empty() )
                req.path.push_back(buffer);
            break;
        }
        buffer.push_back(ch);
        if ( ch == '/' ){
            req.path.push_back(buffer);
            buffer.clear();
        }
    }
}

String readKey(std::istream &stream)
{
    String buffer;
    char ch;
    while ( stream.get(ch) ){
        if ( ch == '&' || ch == '=' || ch == ' ' ){
            stream.putback(ch);
            break;
        }
        buffer.push_back(ch);
    }
    return buffer;
}

void readQuary(std::istream &stream, HTTP_Request &req)
{
    QuaryPair buffer;
    bool hasKey = false;
    char ch;
    while ( stream.get(ch) ){
        if ( ch == '?' || ch == '&' ){
            if ( hasKey ){
                req.quary.push_back(buffer);
            }
            buffer.key = urlDecode( readKey(stream) );
            hasKey = true;
        }
        if ( ch == '=' ){
            buffer.value = urlDecode( readKey(stream) );
        }
        if ( ch == ' ' ){
            if ( !buffer.key.empty() )
                req.quary.push_back(buffer);
            break;
        }
    }
}

std::istream &operator>>(std::istream &stream, HTTP_Request &req)
{
    String type;
    stream >> type;
    if ( type == "GET" ){
        req.type = HTTP_Request_GET;
    }
    readPath(stream, req);
    readQuary(stream, req);
    return stream;
}
