//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_BYTEARRAY_H
#define EASYBITCOIN_BYTEARRAY_H

#include <vector>

typedef unsigned char Byte;

class ByteArray : public std::vector<Byte>
{
public:
    ByteArray();

    ByteArray(std::vector::size_type len);
};


#endif //EASYBITCOIN_BYTEARRAY_H
