// Copyright (c) 2015 Sebastian Geisler
// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.


#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

#include <ByteArray.h>
#include <Conversions.h>
#include <BtcPrivateKey.h>
#include <TransactionInput.h>
#include <Transaction.h>

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

TEST_CASE("Encode base58 check", "[toBase58Check]")
{
    REQUIRE(Conversions::toBase58Check(Conversions::fromBase58Check("1LtyTmydQP28esyweRn2mJog5FkQxRh6LD", 0), 0) ==
            "1LtyTmydQP28esyweRn2mJog5FkQxRh6LD");
}

TEST_CASE("privKey to pubKey to address")
{
    BtcPrivateKey privKey(Conversions::fromBase58Check("L4rK1yDtCWekvXuE6oXD9jCYfFNV2cWRpVuPLBcCU2z8TrisoyY1", 0x80));
    REQUIRE(Conversions::toHex(privKey.getPublicKey()) ==
            "03a34b99f22c790c4e36b2b3c2c35a36db06226e41c692fc82b8b56ac1c540c5bd");
    REQUIRE(privKey.getPublicKey().getAddress() == "1F3sAm6ZtwLAUnj7d38pGFxtP3RVEvtsbV");

    BtcPrivateKey privKey2(Conversions::fromBase58Check("5KYZdUEo39z3FPrtuX2QbbwGnNP5zTd7yyr2SC1j299sBCnWjss", 0x80));
    REQUIRE(Conversions::toHex(privKey2.getPublicKey()) ==
            "04a34b99f22c790c4e36b2b3c2c35a36db06226e41c692fc82b8b56ac1c540c5bd5b8dec5235a0fa8722476c7709c02559e3aa73aa03918ba2d492eea75abea235");
    REQUIRE(privKey2.getPublicKey().getAddress() == "1HZwkjkeaoZfTSaJxDw6aKkxp45agDiEzN");
}

TEST_CASE("signing")
{
    ByteArray hash = Conversions::fromHex("1234567890abcdef").sha256();
    BtcPrivateKey privKey("L4rK1yDtCWekvXuE6oXD9jCYfFNV2cWRpVuPLBcCU2z8TrisoyY1");
    BtcPublicKey pubKey = privKey.getPublicKey();
    ByteArray sig = privKey.sign(hash);
    ByteArray falseSig = sig;
    falseSig[0] = 0xab;

    REQUIRE(pubKey.checkSig(hash, sig) == true);

    REQUIRE(pubKey.checkSig(hash, falseSig) == false);
}

TEST_CASE("uint32 to bytes", "[fromUInt32]")
{
    REQUIRE(Conversions::toHex(Conversions::fromUInt32(1234)) == "d2040000");
}

TEST_CASE("VarInt to bytes", "[fromVarInt]")
{
    REQUIRE(Conversions::toHex(Conversions::fromVarInt(1234567)) == "fe87d61200");
}

TEST_CASE("txIn get PubKeyHash")
{
    REQUIRE(TransactionInput(ByteArray(),
                             0,
                             Conversions::fromHex("76a914b7675e0b90a09cb97674702be07b119c989b835088ac"),
                             0)
                    .getPubKeyHash().toHex() == "b7675e0b90a09cb97674702be07b119c989b8350");
}

TEST_CASE("sign tx")
{
    Transaction t;
    t.addInput(TransactionInput(Conversions::reverse(
            Conversions::fromHex("c8ab2a4fde8029c72f9689f653871f634c6a51bcd0fd4010b6995702b9713988")), 0,
                                Conversions::fromHex("76a914b7675e0b90a09cb97674702be07b119c989b835088ac"), 100000));
    t.addOutput(TransactionOutput("1HikVCL5PsR75toN23yEifLqmg8uXAepoz", 90000));
    t.signPubKeyHashInput(0, BtcPrivateKey("L5G5BA4Veb4qvbgFHH4bNwVxJkRnAkSq8QUbPQ5YR57FZdKBPzm8"));

    REQUIRE(t.isSigned());
    //for testing:
    //std::cout << t.serializeTransaction().toHex() << std::endl;
}

TEST_CASE("ByteArray getSection")
{
    REQUIRE(Conversions::fromHex("12345678").getSection(1, 2).toHex() == "3456");
}

TEST_CASE("ByteArray to scriptVarInt")
{
    REQUIRE(Conversions::toScriptVarInt(Conversions::fromScriptVarInt(0)) == 0);
    REQUIRE(Conversions::toScriptVarInt(Conversions::fromScriptVarInt(1)) == 1);
    REQUIRE(Conversions::toScriptVarInt(Conversions::fromScriptVarInt(123456)) == 123456);
    REQUIRE(Conversions::toScriptVarInt(Conversions::fromScriptVarInt(-1)) == -1);
    REQUIRE(Conversions::toScriptVarInt(Conversions::fromScriptVarInt(-123456)) == -123456);
}

TEST_CASE("create new PrivKey")
{
    BtcPrivateKey key;
    ByteArray hash = Conversions::fromHex("123456").sha256();
    ByteArray sig = key.sign(hash);

    REQUIRE(key.getPublicKey().checkSig(hash, sig));
}