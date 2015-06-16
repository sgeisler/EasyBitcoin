//
// Created by Sebastian on 27.05.2015.
//

#ifndef EASYBITCOIN_TRANSACTIONINPUT_H
#define EASYBITCOIN_TRANSACTIONINPUT_H


#include "BtcPrivateKey.h"
#include "stdint.h"

struct TransactionInput
{
    TransactionInput(const ByteArray &reversePrevHash,
                     uint32_t outputIndex,
                     const ByteArray &script,
                     uint64_t value,
                     uint32_t sequence = 0xffffffff,
                     bool isSigned = false);

    ByteArray reversePrevHash;
    uint32_t outputIndex;
    ByteArray script;
    uint32_t sequence;
    uint64_t value;

    bool isSigned;

    bool isPayToPubKeyHash();

    ByteArray getPubKeyHash();
};


#endif //EASYBITCOIN_TRANSACTIONINPUT_H
