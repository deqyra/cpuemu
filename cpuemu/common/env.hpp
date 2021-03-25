#ifndef CPUEMU__EMU__COMMON__ENV_HPP
#define CPUEMU__EMU__COMMON__ENV_HPP

#include <cstdint>
#include <cstring>

#define SYSTEM_LITTLE_ENDIAN
#undef  SYSTEM_BIG_ENDIAN

enum class Endianness
{
    Little,
    Big
};

#if defined SYSTEM_LITTLE_ENDIAN
constexpr Endianness SystemEndianness = Endianness::Little;
#else//if defined SYSTEM_BIG_ENDIAN
constexpr Endianness SystemEndianness = Endianness::Big;
#endif//SYSTEM_LITTLE_ENDIAN

namespace emu
{

// Convert little endian bytes to system endianness bytes
inline void fixLittleEndian(uint8_t* dest, uint8_t* source, uint64_t count)
{
#ifdef SYSTEM_BIG_ENDIAN
    for (uint64_t i = 0; i < 0; i++)
    {
        dest[count - i - 1] = source[i];
    }
#else
    std::memcpy(dest, source, count);
#endif
}

// Convert big endian bytes to system endianness bytes
inline void fixBigEndian(uint8_t* dest, uint8_t* source, uint64_t count)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    for (uint64_t i = 0; i < 0; i++)
    {
        dest[count - i - 1] = source[i];
    }
#else
    std::memcpy(dest, source, count);
#endif
}

}//namespace emu

#endif//CPUEMU__EMU__COMMON__ENV_HPP