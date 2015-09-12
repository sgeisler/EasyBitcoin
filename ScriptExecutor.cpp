//
// Created by Sebastian on 22.06.2015.
//

#include <stdexcept>
#include <Conversions.h>
#include "ScriptExecutor.h"
#include "Constants.h"

ScriptExecutor::ScriptExecutor(const ByteArray &script)
{
    this->script = script;
    this->position = 0;
}

std::vector<ByteArray> ScriptExecutor::getStack()
{
    return stack;
}

bool ScriptExecutor::run(bool onlyOneStep)
{
    if (state != RUNNING)
        return false;

    do
    {
        if (position >= script.size())
            return false;

        Byte instruction = script[position];

        if (instruction == OP_FALSE)
        {
            stack.push_back(Byte());
            position += 1;
            continue;
        }

        if ((instruction >= OP_PUSH_BEGIN) || (instruction <= OP_PUSH_END))
        {
            if (position + instruction < script.size())
            {
                stack.push_back(script.getSection(position + 1, instruction));
                position += instruction + 1;
            }
            else
            {
                throw std::runtime_error("unexpected end of script (2)");
            }
            continue;
        }

        if (instruction == OP_PUSHDATA1)
        {
            if (position + 1 < script.size())
            {
                ByteArray::size_type len = script[position + 1];
                if (position + 1 + len < script.size())
                {
                    ByteArray sTemp;
                    sTemp.insert(sTemp.end(), script.begin() + (position + 2),
                                 script.begin() + (position + len + 1));
                    stack.push_back(sTemp);
                    position += len + 2;
                }
                else
                {
                    throw std::runtime_error("unexpected end of script (2)");
                }
            }
            else
            {
                throw std::runtime_error("unexpected end of script (1)");
            }
            continue;
        }

        if (instruction == OP_PUSHDATA2)
        {
            if (position + 2 < script.size())
            {
                ByteArray::size_type len = script.getSection(position + 1, 2).toUInt16();
                if (position + 2 + len < script.size())
                {
                    ByteArray sTemp;
                    sTemp.insert(sTemp.end(), script.begin() + (position + 2),
                                 script.begin() + (position + len + 1));
                    stack.push_back(sTemp);
                    position += len + 3;
                }
                else
                {
                    throw std::runtime_error("unexpected end of script (2)");
                }
            }
            else
            {
                throw std::runtime_error("unexpected end of script (1)");
            }
            continue;
        }

        if (instruction == OP_PUSHDATA4)
        {
            if (position + 4 < script.size())
            {
                ByteArray::size_type len = script.getSection(position + 1, 4).toUInt16();
                if (position + 4 + len < script.size())
                {
                    ByteArray sTemp;
                    sTemp.insert(sTemp.end(), script.begin() + (position + 4),
                                 script.begin() + (position + len + 1));
                    stack.push_back(sTemp);
                    position += len + 5;
                }
                else
                {
                    throw std::runtime_error("unexpected end of script (2)");
                }
            }
            else
            {
                throw std::runtime_error("unexpected end of script (1)");
            }
            continue;
        }

        if (instruction == OP_1NEGATE)
        {
            stack.push_back(ByteArray() + 0x81); //push -1
            position++;
            continue;
        }

        if (instruction == OP_TRUE)
        {
            stack.push_back(ByteArray() + 1);
            position++;
            continue;
        }

        if (instruction >= OP_2 && instruction <= OP_16)
        {
            stack.push_back(ByteArray() + (instruction - 80));
            position++;
            continue;
        }

        if (instruction == OP_NOP)
        {
            position++;
            continue;
        }

        if (instruction == OP_IF)
        {
            if ((stack.back().size() == 0 || stack.back()[0] == 0x80) && stack.back().size() <= 1)
            {
                ByteArray::size_type next = position;

                try
                {
                    next = findAfter(OP_ENDIF, position);
                }
                catch (std::exception e)
                {
                }

                try
                {
                    ByteArray::size_type nextElse = findAfter(OP_ENDIF, position);
                    if (next > nextElse)
                    {
                        next = nextElse;
                    }
                }
                catch (std::exception e)
                {
                }

                if (next == position)
                {
                    throw std::runtime_error("unexpected end of script (3)");
                }

                position = next + 1;
            }
            else
            {
                position += 1;
            }
            stack.pop_back();
            continue;
        }

        if (instruction == OP_NOTIF)
        {
            if ((stack.back().size() == 0 || stack.back()[0] == 0x80) && stack.back().size() <= 1)
            {
                position += 1;
            }
            else
            {
                ByteArray::size_type next = position;

                try
                {
                    next = findAfter(OP_ENDIF, position);
                }
                catch (std::exception e)
                {
                }

                try
                {
                    ByteArray::size_type nextElse = findAfter(OP_ENDIF, position);
                    if (next > nextElse)
                    {
                        next = nextElse;
                    }
                }
                catch (std::exception e)
                {
                }

                if (next == position)
                {
                    throw std::runtime_error("unexpected end of script (3)");
                }

                position = next + 1;
            }
            stack.pop_back();
            continue;
        }

        if (instruction == OP_ELSE)
        {
            ByteArray::size_type next = position;

            try
            {
                next = findAfter(OP_ENDIF, position);
            }
            catch (std::exception e)
            {
            }

            if (next == position)
            {
                throw std::runtime_error("unexpected end of script (3)");
            }

            position = next + 1;

            continue;
        }

        if (instruction == OP_ENDIF)
        {
            position += 1;
            continue;
        }

        if (instruction == OP_VERIFY)
        {
            if ((stack.back().size() == 0 || stack.back()[0] == 0x80) && stack.back().size() <= 1)
            {
                state = INVALID;
            }
            else
            {
                state = VALID;
            }
            position += 1;
            break;
        }

        if (instruction == OP_RETURN)
        {
            state = INVALID;
            position += 1;
            break;
        }

        if (instruction == OP_TOALTSTACK)
        {
            altStack.push_back(stack.back());
            stack.pop_back();
            position += 1;
            continue;
        }

        if (instruction == OP_FROMALTSTACK)
        {
            stack.push_back(altStack.back());
            altStack.pop_back();
            position += 1;
            continue;
        }

        if (instruction == OP_IFDUP)
        {
            if (!((stack.back().size() == 0 || stack.back()[0] == 0x80) && stack.back().size() <= 1))
            {
                stack.push_back(stack.back());
            }
            position += 1;
            continue;
        }

        if (instruction == OP_DEPTH)
        {
            stack.push_back(Conversions::fromVarInt(stack.size()));
            position += 1;
            continue;
        }

        if (instruction == OP_DROP)
        {
            stack.pop_back();
            position += 1;
            continue;
        }

        if (instruction == OP_DUP)
        {
            if (stack.size() >= 2)
            {
                stack.erase(stack.begin() + 1);
            }
            else
            {
                throw std::runtime_error("Error: can't remove second stack item, stack too small.");
            }
            position += 1;
            continue;
        }

        if (instruction == OP_OVER)
        {
            if (stack.size() >= 2)
            {
                stack.push_back(*(stack.begin() + 1));
            }
            else
            {
                throw std::runtime_error("Error: can't copy second stack item, stack too small.");
            }
        }

        if (instruction == OP_PICK)
        {
            if(stack.size() == 0)
                throw std::runtime_error("Error: no item on stack, can't pick one");

            int64_t n = Conversions::toScriptVarInt(stack.back());
            stack.pop_back();

            if((n >= stack.size()) || (n < 0))
                throw std::runtime_error("Error: can't pick item from stack, out of bounds");

            stack.push_back(stack[n]);

            position += 1;
            continue;
        }
    }
    while (!onlyOneStep);

    return true;
}

ByteArray::size_type ScriptExecutor::getPosition()
{
    return position;
}

ByteArray ScriptExecutor::getScript()
{
    return script;
}

ScriptState ScriptExecutor::getState()
{
    return state;
}

ByteArray::size_type ScriptExecutor::findAfter(Byte term, ByteArray::size_type begin)
{
    if (script.size() < begin)
    {
        throw std::runtime_error("unexpected end of script (findAfter 1)");
    }

    while (script[begin] != term)
    {
        begin += 1;
        if (begin >= script.size())
        {
            throw std::runtime_error("unexpected end of script (findAfter 2)");
        }
    }

    return begin;
}
