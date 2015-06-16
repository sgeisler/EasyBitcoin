//
// Created by Sebastian on 16.06.2015.
//

#include "ByteArray.h"
#include "Crypto.h"

void ByteArray::operator+=(const ByteArray &other)
{
    this->insert(this->end(), other.begin(), other.end());
}

ByteArray ByteArray::operator+(const ByteArray &other) const
{
    ByteArray ret;
    ret.insert(ret.end(), this->begin(), this->end());
    ret.insert(ret.end(), this->begin(), this->end());
    return ret;
}

ByteArray ByteArray::toHex() const
{
    return Conversions::toHex(*this);
}

ByteArray ByteArray::toBase58() const
{
    return Conversions::toBase58(*this);
}

ByteArray ByteArray::toBase58Check(Byte version) const
{
    return Conversions::toBase58Check(*this, version);
}

ByteArray ByteArray::sha256() const
{
    return Crypto::sha256(*this);
}

ByteArray ByteArray::ripemd160() const
{
    return Crypto::ripemd160(*this);
}
