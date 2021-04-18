#ifndef CPUEMU__COMMON__BUS__BUS8_HPP
#define CPUEMU__COMMON__BUS__BUS8_HPP

#include "bus.hpp"
#include "../types.hpp"

namespace emu
{

template<BusMode Mode>
class Bus<8, Mode>
{
public:
    using integral_type = Byte;

    integral_type& operator integral_type();
    integral_type& operator=(const integral_type& i);
};

}//namespace cpuemu


#endif//CPUEMU__COMMON__BUS__BUS8_HPP