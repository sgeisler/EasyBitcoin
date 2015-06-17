//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_BYTEARRAY_H
#define EASYBITCOIN_BYTEARRAY_H

#include <vector>
#include <string>

class ByteArray;
typedef unsigned char Byte;

class ByteArray : public std::vector<Byte>
{
public:
    /*!
     * initializes empty ByteArray
     */
    ByteArray() : std::vector<Byte>()
    {
    };

    /*!
     * initializes ByteArray of given length filled with 0x00
     * @param len length of ByteArray
     */
    ByteArray(std::vector<Byte>::size_type len) : std::vector<Byte>(len)
    {
    };

    /*!
     * appends ByteArray
     * @param other ByteArray to append to this
     */
    void operator+=(const ByteArray &other);

    /*!
     * appends single Byte
     * @param other Byte to append to this
     */
    void operator+=(const Byte &other);

    /*!
     * appends ByteArray and returns result
     * @param other ByteArray to append
     * @return this and other concatenated
     */
    ByteArray operator+(const ByteArray &other) const;

    /*!
     * encodes ByteArray to a hex string
     * @return hex representation
     */
    std::string toHex() const;

    /*!
     * encodes ByteArray to base58
     * @return base58 representation
     */
    std::string toBase58() const;

    /*!
     * encodes ByteArray to base58 and adds checksum and version byte
     * @param version version byte
     * @return base58check representation
     */
    std::string toBase58Check(Byte version) const;

    /*!
     * @return sha256 hash of ByteArray
     */
    ByteArray sha256() const;

    /*!
     * @return ripemd160 hash of ByteArray
     */
    ByteArray ripemd160() const;
};


#endif //EASYBITCOIN_BYTEARRAY_H
