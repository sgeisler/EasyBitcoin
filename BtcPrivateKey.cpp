//
// Created by sebastian on 25.05.15.
//

#include <stdexcept>
#include <Crypto.h>
#include "BtcPrivateKey.h"
#include "Constants.h"

BtcPrivateKey::BtcPrivateKey(const ByteArray &key)
{
    if (key.size() == EC_PRIVATE_KEY_LENGTH) {
        this->key = key;
        this->compressed = false;
        return;
    }
    else if (key.size() == EC_PRIVATE_KEY_LENGTH + 1) {
        if (key.back() == 1) {
            this->key.insert(this->key.begin(), key.begin(), key.begin() + EC_PRIVATE_KEY_LENGTH);
            this->compressed = true;
        }
    }

    throw std::runtime_error("Wrong key size!");
}

ByteArray BtcPrivateKey::getPrivateKey() const
{
    return key;
}

ByteArray BtcPrivateKey::getPublicKey() const
{
    if (compressed) {
        return Crypto::privKeyToCompressedPubKey(key);
    }
    else {
        return Crypto::privKeyToPubKey(key);
    }
}

ByteArray BtcPrivateKey::sign(const ByteArray &hash) const
{
    return Crypto::sign(key, hash);
}