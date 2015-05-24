//
// Created by Sebastian on 24.05.2015.
//

#include "ByteArray.h"

ByteArray::ByteArray() : vector()
{
}

ByteArray::ByteArray(std::vector::size_type len) : vector<Byte>(len)
{
}