#ifndef CPUEMU__COMMON__BUS__BUS_HPP
#define CPUEMU__COMMON__BUS__BUS_HPP

#include <cstdint>

#include "bus_mode.hpp"

namespace emu
{

template<uint8_t Size, BusMode Mode>
class Bus
{
public:
    using integral_type = void;

    Bus() = delete;

    integral_type& operator integral_type() = delete;
    integral_type& operator=(const integral_type& i) = delete;
};

}//namespace cpuemu


#endif//CPUEMU__COMMON__BUS__BUS_HPP