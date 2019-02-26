#ifndef GZIP_H
#define GZIP_H

#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

class Gzip {
public:
    static std::string compress(const std::string& data);

    static std::string decompress(const std::string& data);
};

#endif // GZIP_H
