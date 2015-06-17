//
// Created by Sebastian on 27.05.2015.
//

#ifndef EASYBITCOIN_TRANSACTION_H
#define EASYBITCOIN_TRANSACTION_H


#include <vector>
#include <stdint.h>

#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "BtcPrivateKey.h"

class Transaction
{
public:
    void addInput(const TransactionInput &inp);

    void addOutput(const TransactionOutput &out);

    uint64_t getFees();

    uint64_t getRecommendedFees();

    ByteArray getHashAllForInput(std::vector<TransactionInput>::size_type inputNumber);

    void signPubKeyHashInput(std::vector<TransactionInput>::size_type inputNumber, const BtcPrivateKey &privKey);

    bool isSigned();

    ByteArray serializeTransaction();

    std::vector<TransactionInput> inputs;
    std::vector<TransactionOutput> outputs;
};


#endif //EASYBITCOIN_TRANSACTION_H
