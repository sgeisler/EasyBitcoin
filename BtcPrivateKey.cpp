//
// Created by sebastian on 25.05.15.
//

#include <stdexcept>

#include "Crypto.h"
#include "Conversions.h"
#include "BtcPublicKey.h"
#include "BtcPrivateKey.h"
#include "Constants.h"

BtcPrivateKey::BtcPrivateKey(const ByteArray &key) : ByteArray()
{
    if (key.size() == EC_PRIVATE_KEY_LENGTH) {
        this->insert(this->begin(), key.begin(), key.end());
        this->compressed = false;
        return;
    }
    else if (key.size() == EC_PRIVATE_KEY_LENGTH + 1) {
        if (key.back() == 1) {
            this->insert(this->begin(), key.begin(), key.begin() + EC_PRIVATE_KEY_LENGTH);
            this->compressed = true;
            return;
        }
    }

    throw std::runtime_error("Wrong key size!");
}

BtcPublicKey BtcPrivateKey::getPublicKey() const
{
    if (compressed) {
        return Crypto::privKeyToCompressedPubKey(*this);
    }
    else {
        return Crypto::privKeyToPubKey(*this);
    }
}

ByteArray BtcPrivateKey::sign(const ByteArray &hash) const
{
    return Crypto::sign(*this, hash);
}

