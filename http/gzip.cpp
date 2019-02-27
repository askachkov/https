#include "gzip.h"
#include <zlib.h>
#include <memory.h>

#pragma pack(push, 1)

//RFC-1952

struct GZipBuffer
{
    uint32_t zSize;
    uint32_t totalSize;
    union {
        struct {
            uint8_t ID1;
            uint8_t ID2;
            uint8_t CM;
            uint8_t FLG;
            uint32_t MTIME;
            uint8_t XFL;
            uint8_t OS;
            uint8_t compressedBuffer[0xFFFF];
        };
        struct {
            uint8_t unused[8];
            uint8_t zlibBuffer[];
        };
        uint8_t data[0xFFFF];
    };
};

struct GZipSuffix
{
    uint32_t crc32;//uLong crc32 (uLong crc, const Bytef *buf, uInt len);
    uint32_t isize;//This contains the size of the original (uncompressed) input data modulo 2^32.
};

#pragma pack(pop)

GZipBuffer getBuffer()
{
    GZipBuffer res;
    res.ID1 = 31;  // majic constant
    res.ID2 = 139; // gzip format
    res.CM = 8;    // deflate
    res.FLG = 1;   // text data
    res.MTIME = 0; // last changed
    res.totalSize = 10; // Header size;
    return res;
}

GZipSuffix getSuffix(const GZipBuffer & buf)
{
    uint32_t crc = crc32(0L, Z_NULL, 0);
    for (uint32_t i = 0; i < buf.zSize; ++i) {
        crc = crc32(crc, &buf.compressedBuffer[i], 1);
    }
    GZipSuffix res;
    res.crc32 = crc;
    return res;
}

std::string Gzip::compress(const std::string &data)
{
    GZipBuffer buf = getBuffer();
    if (::compress((Bytef*)buf.zlibBuffer, (uLongf*)&buf.zSize, (Bytef*)data.c_str(), data.length()) == Z_OK){
        //fulfil header
        buf.XFL = 2;   // high compression
        buf.OS = 255;  // OS
        //shrink zlib suffix
        buf.zSize -= 4;//4 bytes in suffix
        GZipSuffix suff = getSuffix(buf);
        suff.isize = data.size();
        //copy suffix
        memcpy(&buf.compressedBuffer[buf.zSize], &suff, sizeof(suff));
        buf.totalSize += buf.zSize;
        buf.totalSize += sizeof(suff);
        return std::string((char*)buf.data, buf.totalSize);
    }
    return "";
}
