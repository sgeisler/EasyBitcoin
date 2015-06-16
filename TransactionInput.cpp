//
// Created by Sebastian on 27.05.2015.
//

#include <stdexcept>
#include "TransactionInput.h"

#include "Conversions.h"
#include "Crypto.h"
#include "Constants.h"

TransactionInput::TransactionInput(const ByteArray &reversePrevHash,
                                   uint32_t outputIndex,
                                   const ByteArray &script,
                                   uint64_t value,
                                   uint32_t sequence,
                                   bool isSigned)
        : reversePrevHash(reversePrevHash),
          outputIndex(outputIndex),
          script(script),
          sequence(sequence),
          value(value),
          isSigned(isSigned)
{
}

bool TransactionInput::isPayToPubKeyHash()
{
    if (script.size() != 25)
        return false;

    if (script[0] != OP_DUP)
        return false;

    if (script[1] != OP_HASH160)
        return false;

    if (script[2] != 0x14)
        return false;

    if (script[23] != OP_EQUALVERIFY)
        return false;

    if (script[24] != OP_CHECKSIG)
        return false;

    return true;
}

ByteArray TransactionInput::getPubKeyHash()
{
    if (!isPayToPubKeyHash())
        throw std::runtime_error("Transaction isn't PayToPubKeyHash");

    ByteArray ret;
    ret.insert(ret.end(), script.begin() + 3, script.begin() + 23);

    return ret;
}