//
// Created by Sebastian on 24.05.2015.
//

#include "Crypto.h"

#include "Constants.h"

#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <openssl/ssl.h>

ByteArray Crypto::sha256(const ByteArray &input)
{
    ByteArray ret(SHA256_DIGEST_LENGTH);
    SHA256(&input[0], input.size(), &ret[0]);

    return ret;
}

ByteArray Crypto::ripemd160(const ByteArray &input)
{
    ByteArray ret(RIPEMD160_DIGEST_LENGTH);
    RIPEMD160(&input[0], input.size(), &ret[0]);

    return ret;
}

ByteArray Crypto::sign(const ByteArray &privKey, const ByteArray hash)
{
    // I found 74 as the max. sig. len., but can't confirm
    // if somebody can confirm this it would be great (then
    // I would add it as a constant.
    ByteArray signature(74);

    unsigned int sigSize;
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);
    BIGNUM *bn = BN_bin2bn(&privKey[0], EC_PRIVATE_KEY_LENGTH, NULL);

    EC_KEY_set_private_key(key, bn);
    ECDSA_sign(0, &hash[0], hash.size(), &signature[0], &sigSize, key);

    EC_KEY_free(key);
    BN_free(bn);

    signature.resize(sigSize);

    return signature;
}

ByteArray Crypto::privKeyToPubKey(const ByteArray &privKey)
{
    ByteArray pubKey(EC_PUBLIC_KEY_LENGTH);

    BIGNUM *privBn = BN_bin2bn(&privKey[0], EC_PRIVATE_KEY_LENGTH, NULL);
    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *point = EC_POINT_new(group);
    BN_CTX *ctx = BN_CTX_new();

    EC_POINT_mul(group, point, privBn, NULL, NULL, ctx);
    EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED, &pubKey[0], EC_PUBLIC_KEY_LENGTH, ctx);

    BN_CTX_free(ctx);
    EC_POINT_free(point);
    EC_GROUP_free(group);
    BN_free(privBn);

    return pubKey;
}

ByteArray Crypto::privKeyToCompressedPubKey(const ByteArray &privKey)
{
    ByteArray pubKey(EC_COMPRESSED_PUBLIC_KEY_LENGTH);

    BIGNUM *privBn = BN_bin2bn(&privKey[0], EC_PRIVATE_KEY_LENGTH, NULL);
    EC_GROUP *group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT *point = EC_POINT_new(group);
    BN_CTX *ctx = BN_CTX_new();

    EC_POINT_mul(group, point, privBn, NULL, NULL, ctx);
    EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED, &pubKey[0], EC_COMPRESSED_PUBLIC_KEY_LENGTH, ctx);

    BN_CTX_free(ctx);
    EC_POINT_free(point);
    EC_GROUP_free(group);
    BN_free(privBn);

    return pubKey;
}