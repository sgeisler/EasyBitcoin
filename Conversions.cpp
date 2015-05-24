//
// Created by Sebastian on 24.05.2015.
//

#include "Conversions.h"
#include <stdexcept>

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