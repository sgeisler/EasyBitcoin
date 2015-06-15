//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_CONVERSIONS_H
#define EASYBITCOIN_CONVERSIONS_H

#include <string>

#include "ByteArray.h"

class Conversions
{
public:
    /*!
     * Converts hex std::string to ByteArray, if the string has an odd size a '0' will be appended.
     *
     * @param hex hex string
     * @see ByteArray
     * @return ByteArray of the converted hex string
     */
    static ByteArray fromHex(const std::string &hex);

    /*!
     * Encodes a ByteArray to hex string
     * @param bytes data to encode
     * @return hex encoded data
     */
    static std::string toHex(const ByteArray &bytes);

    /*!
     * Converts base58 string to ByteArray
     * @param base58 string with base58 encoded data
     * @return ByteArray with the converted data
     */
    static ByteArray fromBase58(const std::string &base58);

    /*!
     * Converts base58 string to ByteArray and performs signature check (throws runtime_error if it fails)
     * @param base58 string with base58 encoded data
     * @param version expected version byte (first byte)
     * @return ByteArray with the converted data
     */
    static ByteArray fromBase58Check(const std::string &base58, Byte version);

    /*!
     * Encodes ByteArray base58
     * @param data data that will be encoded
     * @return string with base58 encoded data
     */
    static std::string toBase58(const ByteArray &data);

    /*!
     * Encodes data base58 and adds hash for checking integrity
     * @param data data that will be encoded
     * @param version version byte (first byte) of the resulting string
     * @return base58 encoded data with hash
     */
    static std::string toBase58Check(ByteArray data, Byte version);

    /*!
     * @param num integer that will be encoded to ByteArray
     * @return byte representation of num
     */
    static ByteArray fromUInt32(uint32_t num);
};


#endif //EASYBITCOIN_CONVERSIONS_H
