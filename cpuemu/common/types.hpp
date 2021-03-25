#ifndef CPUEMU__COMMON__TYPES_HPP
#define CPUEMU__COMMON__TYPES_HPP

#include <cstdint>

#include "env.hpp"

namespace emu
{

using Byte = uint8_t;

template<Endianness E>
struct Word;

template<>
struct Word<Endianness::Little>
{
    Byte l;
    Byte h;

    Word<Endianness::Little>& operator=(uint16_t v);
    Word<Endianness::Little>& operator+(Word<Endianness::Little> w);
    Word<Endianness::Little>& operator-(Word<Endianness::Little> w);
    Word<Endianness::Little>& operator++();
    Word<Endianness::Little>& operator++(int);
    Word<Endianness::Little>& operator--();
    Word<Endianness::Little>& operator--(int);
    operator uint16_t();
};

template<>
struct Word<Endianness::Big>
{
    Byte h;
    Byte l;

    Word<Endianness::Big>& operator=(uint16_t v);
    Word<Endianness::Big>& operator+(Word<Endianness::Big> w);
    Word<Endianness::Big>& operator-(Word<Endianness::Big> w);
    Word<Endianness::Big>& operator++();
    Word<Endianness::Big>& operator++(int);
    Word<Endianness::Big>& operator--();
    Word<Endianness::Big>& operator--(int);
    operator uint16_t();
};

}

#endif//CPUEMU__COMMON__TYPES_HPP