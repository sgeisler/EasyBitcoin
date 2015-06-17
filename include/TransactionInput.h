//
// Created by Sebastian on 27.05.2015.
//

#ifndef EASYBITCOIN_TRANSACTIONINPUT_H
#define EASYBITCOIN_TRANSACTIONINPUT_H


#include "BtcPrivateKey.h"
#include "stdint.h"

struct TransactionInput
{
    /*!
     * @param reversePrevHash reversed hash of the transaction of the input
     * @param outputIndex index of the input (output index of the tx)
     * @param script script of the input
     * @param value value of the input
     * @param sequence 0xffffffff, could be used to replace tx later
     * @param isSigned if the script is the output script or the signed input script
     */
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

    /*!
     * @return if the tx pays to the owner of the key with the given hash
     */
    bool isPayToPubKeyHash();

    /*!
     * @return pubKeyHash of the key that can sign the tx
     */
    ByteArray getPubKeyHash();
};


#endif //EASYBITCOIN_TRANSACTIONINPUT_H
