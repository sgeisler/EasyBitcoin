//
// Created by Sebastian on 24.05.2015.
//

#include "ByteArray.h"

ByteArray::ByteArray() : vector<Byte>()
{
}

ByteArray::ByteArray(std::vector<Byte>::size_type len) : vector<Byte>(len)
{
}