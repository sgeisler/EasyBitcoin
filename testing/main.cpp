#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

#include <ByteArray.h>
#include <Conversions.h>

using namespace std;

TEST_CASE("HEX to ByteArray", "[fromHex]")
{
    REQUIRE(Conversions::fromHex("ff")[0] == 255);
    REQUIRE(Conversions::fromHex("f")[0] == 15 * 16);
    REQUIRE(Conversions::fromHex("1a")[0] == 26);

    SECTION("Catch wrong chars")
    {
        bool worked = false;
        try
        {
            ByteArray b = Conversions::fromHex("1x");
        }
        catch (runtime_error &e)
        {
            worked = true;
        }
        REQUIRE(worked);
    }
};