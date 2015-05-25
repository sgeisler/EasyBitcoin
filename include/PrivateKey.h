//
// Created by sebastian on 25.05.15.
//

#ifndef EASYBITCOIN_PRIVATEKEY_H
#define EASYBITCOIN_PRIVATEKEY_H


#include "ByteArray.h"

class PrivateKey {
public:
    /*
     * @param key private key binary representation
     */
    PrivateKey(const ByteArray &key);

    /*
     * @return private key
     */
    ByteArray getPrivateKey() const;

    /*
     * @return compressed or uncompressed public key
     */
    ByteArray getPublicKey() const;

    /*
     * @param hash data to sign
     * @return signed data
     */
    ByteArray sign(const ByteArray &hash) const;

private:
    ByteArray key;
    bool compressed;
};


#endif //EASYBITCOIN_PRIVATEKEY_H
