//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_CONVERSIONS_H
#define EASYBITCOIN_CONVERSIONS_H

#include <string>

#include "ByteArray.h"

class Conversions
{
public:
    /*
     * Converts hex std::string to ByteArray, if the string has an odd size a '0' will be appended.
     *
     * @param hex hex string
     * @see ByteArray
     * @return ByteArray of the converted hex string
     */
    static ByteArray fromHex(const std::string &hex);
};


#endif //EASYBITCOIN_CONVERSIONS_H
