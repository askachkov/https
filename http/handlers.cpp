#include "handlers.h"
#include <algorithm>

HTTP_Response helpHandler(const HTTP_Request &req)
{
    HTTP_Response res;
    std::string body("<PRE>");
    body+= "mirror";
    body += '\n';
    body += '\n';
//    for ( int i = 0; i < req.path.size(); ++i ){
//        body += req.path[i] + ' ';
//    }
    body += req.path;
    body += '\n';
    for ( size_t i = 0; i < req.quary.size(); ++i ){
        body += req.quary[i].key + '=' + req.quary[i].value + '\n';
    }
    body+= "</PRE>";

    res.body = body;
    res.header = getDefaultHeader(HTTP1_1_OK, TEXT_HTML);
    return res;
}

HTTP_Response indexHandler(const HTTP_Request &)
{
    HTTP_Response res;
    res.body = readFile("/index.htm");
    res.header = getDefaultHeader(HTTP1_1_OK, TEXT_HTML);
    return res;
}

HTTP_ContentTypes getTypeByPath(const std::string path)
{
    using namespace std;
    const string PNG = ".png";
    const string HTM = ".htm";
    if (equal(PNG.rbegin(), PNG.rend(), path.rbegin())){
        return IMG_PNG;
    }
    if ( equal(HTM.rbegin(), HTM.rend(), path.rbegin()) ) {
        return TEXT_HTML;
    }
    return TEXT_HTML;
}

HTTP_Response fileHandler(const HTTP_Request &req)
{
    HTTP_Response res;
    res.body = readFile(req.path);
    std::cout << "File length:" << res.body.size() << "|" << req.path << std::endl;
    if ( res.body.empty() ){
        res.header = get404Header();
    } else {
        res.header = getDefaultHeader(HTTP1_1_OK, getTypeByPath(req.path));
    }
    return res;
}

HTTP_Response redirectToIndexHandler(const HTTP_Request &)
{
    HTTP_Response res;
    res.header = getRedirectHeader("/index.htm");
    return res;
}
