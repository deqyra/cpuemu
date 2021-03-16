#ifndef CPUEMU__EMU__COMMON__MEMORY_HPP
#define CPUEMU__EMU__COMMON__MEMORY_HPP

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>

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

        implicit operator Byte()
        {
            return data[where];
        }

        void operator=(Byte b)
        {
            data[where] = b;
        }

        template<typename Container>
        static typename std::enable_if<type_utils::is_sized_container<Container>::value, void>::type
        uint64_t operator=(const Container& c)
        {
            using std::size;
            assert(where + size(c) <= Size);

            using std::begin;
            using std::end;
            std::copy(begin(c), end(c), data);
        }
    };

    Byte[Size] data{ 0 };

    _cell& operator[](uint64_t where)
    {
        assert(where < Size);
        return _cell{this, where};
    }

    template<typename Container>
    static typename std::enable_if<type_utils::is_sized_container<Container>::value, void>::type
    uint64_t operator=(const Container& c)
    {
        using std::size;
        assert(size(c) <= Size);

        using std::begin;
        using std::end;
        std::copy(begin(c), end(c), data);

        std::memset(data + size(c), 0, (size_t)(Size - size(c)));
    }
};

}//namespace emu


#endif//CPUEMU__EMU__COMMON__MEMORY_HPP