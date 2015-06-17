//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_BYTEARRAY_H
#define EASYBITCOIN_BYTEARRAY_H

#include <vector>
#include <string>

class ByteArray;
typedef unsigned char Byte;

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

    void operator+=(const Byte &other);

    ByteArray operator+(const ByteArray &other) const;

    std::string toHex() const;

    std::string toBase58() const;

    std::string toBase58Check(Byte version) const;

    ByteArray sha256() const;

    ByteArray ripemd160() const;
};


#endif //EASYBITCOIN_BYTEARRAY_H
