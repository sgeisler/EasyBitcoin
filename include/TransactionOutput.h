//
// Created by Sebastian on 27.05.2015.
//

#ifndef EASYBITCOIN_TRANSACTIONOUTPUT_H
#define EASYBITCOIN_TRANSACTIONOUTPUT_H


#include "ByteArray.h"

#include "stdint.h"
#include "string"

struct TransactionOutput
{
    TransactionOutput(std::string addr, uint64_t value);

    TransactionOutput(ByteArray scriptPubKey, uint64_t value);

    uint64_t value;
    ByteArray scriptPubKey;
};


#endif //EASYBITCOIN_TRANSACTIONOUTPUT_H
