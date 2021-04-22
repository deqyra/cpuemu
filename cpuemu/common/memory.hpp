#ifndef CPUEMU__COMMON__MEMORY_HPP
#define CPUEMU__COMMON__MEMORY_HPP

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

#include <cpptools/type_utils.hpp>

#include "types.hpp"

namespace emu
{

template<uint64_t Size>
struct Memory
{
    struct _cell
    {
        Byte* data;
        uint64_t where;

        operator Byte()
        {
            return data[where];
        }

        void operator=(Byte b)
        {
            data[where] = b;
        }

        void operator=(const std::vector<Byte>& c)
        {
            assert(where + c.size() <= Size);

            std::copy(c.begin(), c.end(), data + where);
        }
    };

    Byte data[Size]{ 0 };

    _cell operator[](uint64_t where)
    {
        assert(where < Size);
        return {data, where};
    }

    template<Endianness E>
    _cell operator[](Word<E> where)
    {
        assert(where < Size);
        return {data, (uint16_t)where};
    }

    uint64_t operator=(const std::vector<Byte>& c)
    {
        using std::size;
        assert(c.size() <= Size);

        using std::begin;
        using std::end;
        std::copy(c.begin(), c.end(), data);

        std::memset(data + c.size(), 0, (size_t)(Size - c.size()));

        return c.size();
    }
};

}//namespace emu


#endif//CPUEMU__COMMON__MEMORY_HPP