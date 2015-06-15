//
// Created by Sebastian on 14.06.2015.
//

#ifndef EASYBITCOIN_BTCPUBLICKEY_H
#define EASYBITCOIN_BTCPUBLICKEY_H


#include "ByteArray.h"

#include <string>

class BtcPublicKey : public ByteArray
{
public:

    /*
     * @param pubKey compressed or uncompressed EC public key
     */
    BtcPublicKey(const ByteArray &pubKey);

    /*
     * @return returns if the key is compressed
     */
    bool isCompressed();

    /*
     * @return the Base58Check encoded address belonging to the key
     */
    std::string getAddress();
};


#endif //EASYBITCOIN_BTCPUBLICKEY_H
