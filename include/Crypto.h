//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_CRYPTO_H
#define EASYBITCOIN_CRYPTO_H

#include "ByteArray.h"

class Crypto
{
public:
    static ByteArray sha256(const ByteArray &input);

    static ByteArray ripemd160(const ByteArray &input);

    static ByteArray sign(const ByteArray &privKey, const ByteArray hash);

    static ByteArray privKeyToPubKey(const ByteArray &privKey);

    static ByteArray privKeyToCompressedPubKey(const ByteArray &privKey);
};


#endif //EASYBITCOIN_CRYPTO_H
