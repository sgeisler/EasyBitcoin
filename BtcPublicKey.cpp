//
// Created by Sebastian on 14.06.2015.
//

#include "BtcPublicKey.h"
#include "Constants.h"
#include "Crypto.h"

#include <stdexcept>
#include <iostream>

BtcPublicKey::BtcPublicKey(const ByteArray &pubKey) : ByteArray()
{
    if ((pubKey.size() == EC_COMPRESSED_PUBLIC_KEY_LENGTH) || (pubKey.size() == EC_PUBLIC_KEY_LENGTH))
    {
        this->insert(this->begin(), pubKey.begin(), pubKey.end());
    }
    else
    {
        throw std::runtime_error("PubKey hasn't the right size");
    }
}

bool BtcPublicKey::isCompressed() const
{
    return (this->size() == EC_COMPRESSED_PUBLIC_KEY_LENGTH);
}

std::string BtcPublicKey::getAddress() const
{
    return Conversions::toBase58Check(Crypto::ripemd160(Crypto::sha256(*this)), 0);
}

bool BtcPublicKey::checkSig(ByteArray hash, ByteArray sig)
{
    try
    {
        return Crypto::checkSig(*this, hash, sig);
    }
    catch(std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}
