#include "utils.h"
#include <memory.h>
#include <fstream>
#include <iostream>

void error(const char *msg)
{
    perror(msg);
    //exit(1);
}

void bzero(void *ptr, size_t size)
{
    memset(ptr, 0, size);
}

/* Converts a hex character to its integer value */
char from_hex(char ch) {
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
char to_hex(char code) {
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

std::string urlDecode(const std::string  & str) {
    const char *pstr = str.c_str();
    std::string buf;
    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                buf.push_back(from_hex(pstr[1]) << 4 | from_hex(pstr[2]));
                pstr += 2;
            }
        } else if (*pstr == '+') {
            buf.push_back(' ');
        } else {
            buf.push_back(*pstr);
        }
        pstr++;
    }
    //*pbuf = '\0';
    return buf;
}

char *urlEncode(const char *str) {
    const char *pstr = str;
    char *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~')
            *pbuf++ = *pstr;
        else if (*pstr == ' ')
            *pbuf++ = '+';
        else
            *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

std::string readFile(const std::string &path)
{
    const std::string p = "/home/as/QtProjects/https/https/http/www";
    std::ifstream file(p + path);
    char buf;
    std::string res;
    while ( file.read(&buf, 1) ){
        res.push_back(buf);
    }
    return res;
}
