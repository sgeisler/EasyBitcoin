//
// Created by Sebastian on 22.06.2015.
//

#ifndef EASYBITCOIN_SCRIPTEXECUTOR_H
#define EASYBITCOIN_SCRIPTEXECUTOR_H

#include "ByteArray.h"
#include "Transaction.h"

enum ScriptState
{
    VALID,
    INVALID,
    RUNNING
};

class ScriptExecutor
{
public:
    ScriptExecutor(const Transaction &t, size_t inputNumber);

    std::vector<ByteArray> getStack();
    bool run(bool onlyOneStep = false);
    ByteArray::size_type getPosition();
    ByteArray getScript();
    ScriptState getState();

private:
    std::vector<ByteArray> stack;
    std::vector<ByteArray> altStack;
    ByteArray script;
    Transaction t;
    size_t inputNumber;
    ByteArray::size_type position;
    ScriptState state;

    ByteArray::size_type findAfter(Byte term, ByteArray::size_type begin = 0);
};


#endif //EASYBITCOIN_SCRIPTEXECUTOR_H
