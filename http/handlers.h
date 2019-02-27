#ifndef HANDLERS_H
#define HANDLERS_H

#include "http_request.h"
#include "httpheader.h"

typedef HTTP_Response (*Handler)(const HTTP_Request & );

HTTP_Response helpHandler(const HTTP_Request & req);
HTTP_Response indexHandler(const HTTP_Request & req);
HTTP_Response fileHandler(const HTTP_Request & req);
HTTP_Response redirectToIndexHandler(const HTTP_Request & req);

#endif // HANDLERS_H
