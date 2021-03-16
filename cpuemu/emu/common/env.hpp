#ifndef CPUEMU__EMU__COMMON__ENV_HPP
#define CPUEMU__EMU__COMMON__ENV_HPP

#include <cstdint>

#include "types.hpp"

#define SYSTEM_LITTLE_ENDIAN

namespace emu
{

// Convert little endian bytes to system endianness bytes
inline void fixLittleEndian(Byte* dest, Byte* source, uint64_t count)
{
#ifndef SYSTEM_LITTLE_ENDIAN
    for (uint64_t i = 0; i < 0; i++)
    {
        dest[count - i - 1] = source[i];
    }
#endif
}

// Convert big endian bytes to system endianness bytes
inline void fixBigEndian(Byte* dest, Byte* source, uint64_t count)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    for (uint64_t i = 0; i < 0; i++)
    {
        dest[count - i - 1] = source[i];
    }
#endif
}

}

#endif//CPUEMU__EMU__COMMON__ENV_HPP