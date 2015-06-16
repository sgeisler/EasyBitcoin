//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_BYTEARRAY_H
#define EASYBITCOIN_BYTEARRAY_H

#include <vector>

class ByteArray;
typedef unsigned char Byte;

#include "Conversions.h"

class ByteArray : public std::vector<Byte>
{
public:
    ByteArray() : std::vector<Byte>()
    {
    };

    ByteArray(std::vector<Byte>::size_type len) : std::vector<Byte>(len)
    {
    };

    void operator+=(const ByteArray &other);

    ByteArray operator+(const ByteArray &other) const;

    ByteArray toHex() const;

    ByteArray toBase58() const;

    ByteArray toBase58Check(Byte version) const;

    ByteArray sha256() const;

    ByteArray ripemd160() const;
};


#endif //EASYBITCOIN_BYTEARRAY_H
