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
    /*
     * initializes empty ByteArray
     */
    ByteArray();

    /*
     * initializes ByteArray of give size filled with 0
     * @param len size of the ByteArray
     */
    ByteArray(std::vector<Byte>::size_type len);
};


#endif //EASYBITCOIN_BYTEARRAY_H
