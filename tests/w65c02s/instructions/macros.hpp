#ifndef TESTS__W65C02S__INSTRUCTIONS__MACROS_HPP
#define TESTS__W65C02S__INSTRUCTIONS__MACROS_HPP

#include <catch2/catch2.hpp>

#define FIND_INSTRUCTION_INFO_OR_FAIL(instruction)                                \
        InstructionInfoData.find(instruction);                                  \
        if (it == InstructionInfoData.end())                                    \
        {                                                                       \
            WARN("/!\\   No data registered for [ "#instruction" ]   /!\\");    \
            FAIL("Failing test...");                                            \
        }

#endif//TESTS__W65C02S__INSTRUCTIONS__MACROS_HPP
