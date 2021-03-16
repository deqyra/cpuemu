#ifndef CPUEMU__COMMON__TYPES_HPP
#define CPUEMU__COMMON__TYPES_HPP

#include <cstdint>

namespace emu
{

using Byte = uint8_t;
using Word = uint16_t;

enum class Endianness
{
    Little,
    Big
};

}

#endif//CPUEMU__COMMON__TYPES_HPP