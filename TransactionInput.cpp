//
// Created by Sebastian on 27.05.2015.
//

#include "TransactionInput.h"

#include "Conversions.h"
#include "Crypto.h"
#include "Constants.h"

TransactionInput::TransactionInput(const ByteArray &reversePrevHash,
                                   uint32_t outputIndex,
                                   const ByteArray &scriptSig,
                                   uint64_t value,
                                   uint32_t sequence,
                                   bool isSigned)
        : reversePrevHash(reversePrevHash),
          outputIndex(outputIndex),
          scriptSig(scriptSig),
          sequence(sequence),
          value(value),
          isSigned(isSigned)
{
}


ByteArray TransactionInput::toBytes() const
{
    ByteArray ret;
    ret.insert(ret.end(), reversePrevHash.begin(), reversePrevHash.end());

    ByteArray outputIndexBytes = Conversions::fromUInt32(outputIndex);
    ret.insert(ret.end(), outputIndexBytes.begin(), outputIndexBytes.end());

    ByteArray scriptLenBytes = Conversions::fromVarInt(scriptSig.size());
    ret.insert(ret.end(), scriptLenBytes.begin(), scriptLenBytes.end());

    ret.insert(ret.end(), scriptSig.begin(), scriptSig.end());

    ByteArray sequenceBytes = Conversions::fromUInt32(sequence);
    ret.insert(ret.end(), sequenceBytes.begin(), sequenceBytes.end());

    return ret;
}

TransactionInput TransactionInput::signPubKeyHashInput(TransactionInput txIn, const BtcPrivateKey &privKey)
{
    ByteArray txInBytes = txIn.toBytes();
    ByteArray sigHashAll = Conversions::fromUInt32(1);
    txInBytes.insert(txInBytes.end(), sigHashAll.begin(), sigHashAll.end());

    ByteArray txInHash = Crypto::sha256(Crypto::sha256(txInBytes));
    ByteArray txInScriptSig = Crypto::sign(privKey, txInHash);

    txIn.scriptSig = ByteArray();
    txIn.scriptSig.push_back((Byte) (txInScriptSig.size() + 1));

    txIn.scriptSig.insert(txIn.scriptSig.end(), txInScriptSig.begin(), txInScriptSig.end());
    txIn.scriptSig.push_back((Byte) 1);

    ByteArray pubKey = privKey.getPublicKey();
    txIn.scriptSig.push_back((Byte) pubKey.size());

    txIn.scriptSig.insert(txIn.scriptSig.end(), pubKey.begin(), pubKey.end());

    txIn.isSigned = true;

    return txIn;
}
