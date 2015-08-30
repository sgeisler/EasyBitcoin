//
// Created by Sebastian on 16.06.2015.
//

#include <stdexcept>
#include "ByteArray.h"
#include "Crypto.h"
#include "Conversions.h"

void ByteArray::operator+=(const ByteArray &other)
{
    this->insert(this->end(), other.begin(), other.end());
}

void ByteArray::operator+=(const Byte &other)
{
    this->push_back(other);
}

ByteArray ByteArray::operator+(const ByteArray &other) const
{
    ByteArray ret;
    ret.insert(ret.end(), this->begin(), this->end());
    ret.insert(ret.end(), this->begin(), this->end());
    return ret;
}

std::string ByteArray::toHex() const
{
    return Conversions::toHex(*this);
}

std::string ByteArray::toBase58() const
{
    return Conversions::toBase58(*this);
}

std::string ByteArray::toBase58Check(Byte version) const
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

ByteArray ByteArray::getSection(ByteArray::size_type begin, ByteArray::size_type len)
{
    if (begin + len > size())
        throw std::range_error("section not in bounds of ByteArray");

    if (len == 0)
        return ByteArray();

    ByteArray ret;
    ret.insert(ret.end(), this->begin() + begin, this->begin() + (begin + len));

    return ret;
}

uint16_t ByteArray::toUInt16()
{
    return Conversions::toUInt16(*this);
}

uint32_t ByteArray::toUInt32()
{
    return Conversions::toUInt32(*this);
}

uint64_t ByteArray::toUInt64()
{
    return Conversions::toUInt64(*this);
}
