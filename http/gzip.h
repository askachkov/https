#ifndef GZIP_H
#define GZIP_H

#include <string>

class Gzip {
public:
    static std::string compress(const std::string& data);
};

#endif // GZIP_H
