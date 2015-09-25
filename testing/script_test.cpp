// Copyright (c) 2015 Sebastian Geisler
// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.


#include <iostream>
#include <Constants.h>
#include <stdexcept>

#include "ScriptExecutor.h"

using namespace std;

int main()
{
    try
    {
        cout << "Script tests:" << endl;

        Transaction t = Transaction();
        t.addInput(TransactionInput(Conversions::reverse(
                                            Conversions::fromHex(
                                                    "c8ab2a4fde8029c72f9689f653871f634c6a51bcd0fd4010b6995702b9713988")),
                                    0,
                                    Conversions::fromHex("76a914b7675e0b90a09cb97674702be07b119c989b835088ac"),
                                    100000));
        t.addOutput(TransactionOutput("1HikVCL5PsR75toN23yEifLqmg8uXAepoz", 90000));

        cout << "hash1: " << t.getHashAllForInput(0).toHex() << endl;

        BtcPrivateKey pk("L5G5BA4Veb4qvbgFHH4bNwVxJkRnAkSq8QUbPQ5YR57FZdKBPzm8");

        t.signPubKeyHashInput(0, pk);

        ByteArray prevOut;
        prevOut += OP_DUP;
        prevOut += OP_HASH160;

        ByteArray hashedAddr = Conversions::fromHex("b7675e0b90a09cb97674702be07b119c989b8350");

        prevOut += hashedAddr.size();
        prevOut += hashedAddr;
        prevOut += OP_EQUALVERIFY;
        prevOut += OP_CHECKSIG;

        cout << "sig: " << t.inputs[0].script.toHex() << endl;
        cout << "pub: " << prevOut.toHex() << endl;

        ScriptExecutor ex(t, 0);

        size_t pos = 0;

        while (ex.run(true))
        {
            cout << "Script: " << ex.getScript().toHex() << endl;
            for (int i = 0; i < (8 + pos * 2); ++i)
                cout << " ";
            cout << "^^" << endl;
            cout << "Stack:" << endl;
            vector<ByteArray> st = ex.getStack();
            for (vector<ByteArray>::iterator i = st.begin(); i != st.end(); ++i)
            {
                cout << (*i).toHex() << "(" << (*i).size() << ")" << endl;
            }
            cout << "####################" << endl;
            pos = ex.getPosition();
        }
    }
    catch(std::runtime_error e)
    {
        cout << e.what();
    }

    return 0;
}