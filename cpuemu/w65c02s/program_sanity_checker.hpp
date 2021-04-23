#ifndef CPUEMU__W65C02S__PROGRAM_SANITY_CHECKER_HPP
#define CPUEMU__W65C02S__PROGRAM_SANITY_CHECKER_HPP

#include <map>
#include <vector>

#include <common/types.hpp>

namespace emu::w65c02s
{
    
enum class SanityCheckError
{
    UnknownInstruction,
};

class ProgramSanityChecker
{
public:
    static std::map<uint64_t, SanityCheckError> CheckProgram(const std::vector<Byte>& program);
};

}

#endif//CPUEMU__W65C02S__PROGRAM_SANITY_CHECKER_HPP