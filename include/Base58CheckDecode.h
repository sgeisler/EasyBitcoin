//
// Created by Sebastian on 17.06.2015.
//

#ifndef EASYBITCOIN_BASE58CHECKDECODE_H
#define EASYBITCOIN_BASE58CHECKDECODE_H

#include "ByteArray.h"

struct Base58CheckDecoded
{
    ByteArray data;
    Byte version;
};

#endif //EASYBITCOIN_BASE58CHECKDECODE_H
