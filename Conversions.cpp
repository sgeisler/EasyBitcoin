//
// Created by Sebastian on 24.05.2015.
//

#include "Conversions.h"
#include <stdexcept>
#include <Crypto.h>
#include <iostream>

ByteArray Conversions::fromHex(const std::string &hex)
{
    ByteArray ret(hex.size() / 2 + (hex.size() % 2));
    for (size_t i = 0; i < hex.size(); i += 1)
    {
        char charVal;
        char charCode = (char) tolower(hex[i]);
        if (charCode >= '0' && charCode <= '9')
        {
            charVal = charCode - '0';
        }
        else if (charCode >= 'a' && charCode <= 'f')
        {
            charVal = (char) (charCode - 'a' + 10);
        }
        else
        {
            throw std::runtime_error("A character in the given string wasn't HEX.");
        }
        if (i % 2 == 1)
        {
            ret[i / 2] += charVal;
        }
        else
        {
            ret[i / 2] += 16 * charVal;
        }
    }

    return ret;
}


std::string Conversions::toHex(const ByteArray &bytes)
{
    std::string base16 = "0123456789abcdef";
    std::string ret;

    for (ByteArray::const_iterator it = bytes.begin(); it != bytes.end(); it++)
    {
        ret.append(1, base16[(*it) / 16]);
        ret.append(1, base16[(*it) % 16]);
    }

    return ret;
}

ByteArray Conversions::fromBase58(const std::string &base58)
{
    ByteArray base256(base58.size() * 733 / 1000 + 1);

    std::string::const_iterator base58It = base58.begin();
    int zeroes = 0;

    while (base58It != base58.end() && *base58It == '1')
    {
        zeroes++;
        base58It++;
    }

    unsigned int carry;
    for (; base58It != base58.end(); base58It++)
    {
        if ((*base58It) >= '1' && (*base58It) <= '9')
        {
            carry = (*base58It) - '1';
        }
        else if ((*base58It) >= 'A' && (*base58It) <= 'H')
        {
            carry = (*base58It) - 'A' + 9;
        }
        else if ((*base58It) >= 'J' && (*base58It) <= 'N')
        {
            carry = (*base58It) - 'J' + 17;
        }
        else if ((*base58It) >= 'P' && (*base58It) <= 'Z')
        {
            carry = (*base58It) - 'P' + 22;
        }
        else if ((*base58It) >= 'a' && (*base58It) <= 'k')
        {
            carry = (*base58It) - 'a' + 33;
        }
        else if ((*base58It) >= 'm' && (*base58It) <= 'z')
        {
            carry = (*base58It) - 'm' + 44;
        }
        else
        {
            throw std::runtime_error("One characte in the string isn't BASE58");
        }

        for (ByteArray::reverse_iterator retIt = base256.rbegin(); retIt != base256.rend(); retIt++)
        {
            carry += 58 * (*retIt);
            *retIt = carry % 256;
            carry /= 256;
        }
    }

    ByteArray ret;
    ByteArray::iterator base256It = base256.begin();

    while (base256It != base256.end() && *base256It == 0)
    {
        base256It++;
    }

    ret.assign(zeroes, 0x00);
    ret.insert(ret.end(), base256It, base256.end());

    return ret;
}

ByteArray Conversions::fromBase58Check(const std::string &base58, Byte version)
{
    ByteArray ret = fromBase58(base58);

    if (ret[0] != version)
    {
        ret.erase(ret.begin() + 1, ret.end());
        throw std::runtime_error("Wrong version byte! (0x" + Conversions::toHex(ret) + ")");
    }

    if (ret.size() <= 4)
    {
        throw  std::runtime_error("data too short (no checksum found)");
    }

    ByteArray checksum = ByteArray(4);
    for (ByteArray::size_type i = 0; i < 4; i += 1)
    {
        checksum[3 - i] = ret.back();
        ret.pop_back();
    }

    ByteArray hash = Crypto::sha256(Crypto::sha256(ret));

    ret.erase(ret.begin(), ret.begin() + 1);

    for (ByteArray::size_type i = 0; i < 4; i += 1)
    {
        if (hash[i] != checksum[i])
        {
            throw std::runtime_error("Checksum not valid, data corrupted?");
        }
    }

    return ret;
}

std::string Conversions::toBase58(const ByteArray &data)
{
    std::string base58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

    ByteArray encoded(data.size() * 138 / 100 + 1);

    ByteArray::const_iterator dataIt = data.begin();
    int zeroes = 0;

    while (dataIt != data.end() && *dataIt == 0)
    {
        zeroes++;
        dataIt++;
    }

    for (; dataIt != data.end(); dataIt++)
    {
        int carry = *dataIt;

        for (ByteArray::reverse_iterator encodedIt = encoded.rbegin(); encodedIt != encoded.rend(); encodedIt++)
        {
            carry += 256 * (*encodedIt);
            *encodedIt = carry % 58;
            carry /= 58;
        }
    }

    ByteArray::iterator encodedIt = encoded.begin();

    while (encodedIt != encoded.end() && *encodedIt == 0)
    {
        encodedIt++;
    }

    std::string ret;
    ret.assign(zeroes, '1');

    while (encodedIt != encoded.end())
    {
        ret += base58[*(encodedIt++)];
    }

    return ret;
}

std::string Conversions::toBase58Check(ByteArray data, Byte version)
{
    data.insert(data.begin(), version);

    ByteArray hash = Crypto::sha256(Crypto::sha256(data));
    data.insert(data.end(), hash.begin(), hash.begin() + 4);

    return toBase58(data);
}

ByteArray Conversions::fromUInt32(uint32_t num)
{
    ByteArray ret(4);

    for (unsigned int bNum = 0; bNum < 4; bNum++)
    {
        ret[3 - bNum] = num / (1 << (8 * (3 - bNum)));
        num %= (1 << (8 * (3 - bNum)));
    }

    return ret;
}

ByteArray Conversions::fromVarInt(uint64_t num)
{
    size_t len;
    Byte firstByte;

    if (num < 0xfd)
    {
        len = 0;
        firstByte = (Byte) num;
    }
    else if (num <= 0xffff)
    {
        len = 2;
        firstByte = 0xfd;
    }
    else if (num <= 0xffffffff)
    {
        len = 4;
        firstByte = 0xfe;
    }
    else
    {
        len = 8;
        firstByte = 0xff;
    }

    ByteArray ret(len + 1);
    ret[0] = firstByte;

    for (int bytePos = len; bytePos >= 1; --bytePos)
    {
        ret[bytePos] = num / (1 << (8 * (bytePos - 1)));
        num %= (1 << (8 * (bytePos - 1)));
    }

    return ret;
}
