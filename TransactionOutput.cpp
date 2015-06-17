//
// Created by Sebastian on 28.05.2015.
//

#include <stdexcept>
#include "TransactionOutput.h"

#include "Constants.h"

TransactionOutput::TransactionOutput(ByteArray scriptPubKey, uint64_t value)
{
    this->scriptPubKey = scriptPubKey;
    this->value = value;
}

TransactionOutput::TransactionOutput(std::string addr, uint64_t value)
{
    ByteArray hash = Conversions::fromBase58Check(addr, 0);

    if (hash.size() != 20)
        throw std::runtime_error("This is not a valid address: " + addr);

    this->scriptPubKey += OP_DUP;
    this->scriptPubKey += OP_HASH160;
    this->scriptPubKey += 0x14;
    this->scriptPubKey += hash;
    this->scriptPubKey += OP_EQUALVERIFY;
    this->scriptPubKey += OP_CHECKSIG;

    this->value = value;
}