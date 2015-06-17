//
// Created by sebastian on 25.05.15.
//

#ifndef EASYBITCOIN_PRIVATEKEY_H
#define EASYBITCOIN_PRIVATEKEY_H


#include "ByteArray.h"
#include "BtcPublicKey.h"

#include "string"

class BtcPrivateKey : public ByteArray
{
public:
    /*!
     * @param key private key binary representation ( = fromBase58Check(WIF))
     */
    BtcPrivateKey(const ByteArray &key);

    /*!
     * @param wifKey wallet import format key
     */
    BtcPrivateKey(const std::string &wifKey);

    /*!
     * @return compressed or uncompressed public key
     */
    BtcPublicKey getPublicKey() const;

    /*!
     * @param hash data to sign
     * @return signed data
     */
    ByteArray sign(const ByteArray &hash) const;

private:
    bool compressed;
};


#endif //EASYBITCOIN_PRIVATEKEY_H
