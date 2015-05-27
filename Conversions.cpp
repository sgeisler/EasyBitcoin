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
    ByteArray ret(base58.size() * 733 / 1000 + 1);

    unsigned int carry;
    for (std::string::const_iterator base58It = base58.begin(); base58It != base58.end(); base58It++)
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

        for (ByteArray::reverse_iterator retIt = ret.rbegin(); retIt != ret.rend(); retIt++)
        {
            carry += 58 * (*retIt);
            *retIt = carry % 256;
            carry /= 256;
        }
    }
    return ret;
}

ByteArray Conversions::fromBase58Check(const std::string &base58, Byte version)
{
    ByteArray ret = fromBase58(base58);
    if (ret[0] != version)
    {
        throw std::runtime_error("Wrong version byte!");
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
