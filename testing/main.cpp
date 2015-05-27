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

TEST_CASE("ByteArray to hex", "[toHex]")
{
    std::string hex = "123fa4ffd900";
    ByteArray ba = Conversions::fromHex(hex);
    REQUIRE(Conversions::toHex(ba) == hex);
};

TEST_CASE("Decode base58", "[fromBase58]")
{
    ByteArray ba = Conversions::fromBase58("1LtyTmydQP28esyweRn2mJog5FkQxRh6LD");
    REQUIRE(Conversions::toHex(ba) == "00da3ebc5a339c2cdf74584108767c68752e5700513d1c606e");
};

TEST_CASE("Decode base58 check", "[fromBase58Check]")
{
    REQUIRE(Conversions::fromBase58Check("1LtyTmydQP28esyweRn2mJog5FkQxRh6LD", 0) ==
            Conversions::fromHex("da3ebc5a339c2cdf74584108767c68752e570051"));

    bool worked = true;
    try
    {
        Conversions::fromBase58Check("1rtyTmydQP28esyweRn2mJog5FkQxRh6LD", 0);
    }
    catch (std::runtime_error e)
    {
        worked = false;
    }

    REQUIRE(worked == false);

    worked = true;
    try
    {
        Conversions::fromBase58Check("1LtyTmydQP28esyweRn2mJog5FkQxRh6LD", 10);
    }
    catch (std::runtime_error e)
    {
        worked = false;
    }

    REQUIRE(worked == false);

}