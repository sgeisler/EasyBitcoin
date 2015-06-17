//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_CRYPTO_H
#define EASYBITCOIN_CRYPTO_H

#include "ByteArray.h"

namespace Crypto
{
    /*!
     * hashes binary data using SHA256
     * @param input binary data that will be hashed
     * @return ByteArray containing the hash
     */
    ByteArray sha256(const ByteArray &input);

    /*!
     * hashes binary data using RIPEMD160
     * @param input binary data that will be hashed
     * @return ByteArray containing the hash
     */
    ByteArray ripemd160(const ByteArray &input);

    /*!
     * Signs binary data using ECDSA
     * @param privKey the private key that should be used
     * @param hash binary data that will be signed
     * @return signed data
     */
    ByteArray sign(const ByteArray &privKey, const ByteArray hash);

    /*!
     * Derives the public key from the private key
     * @param privKey private key
     * @return public key
     */
    ByteArray privKeyToPubKey(const ByteArray &privKey);

    /*!
     * Derives the compressed public key from the private key
     * @param privKey private key
     * @return compressed public key
     */
    ByteArray privKeyToCompressedPubKey(const ByteArray &privKey);
};


#endif //EASYBITCOIN_CRYPTO_H
