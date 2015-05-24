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
    static ByteArray fromHex(const std::string &hex);
};


#endif //EASYBITCOIN_CONVERSIONS_H
