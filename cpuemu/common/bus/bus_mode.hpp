#ifndef CPUEMU__COMMON__BUS__BUS_MODE_HPP
#define CPUEMU__COMMON__BUS__BUS_MODE_HPP

namespace emu
{

enum class BusMode
{
    In    = 0x1,
    Out   = 0x2,
    InOut = In|Out
};

}//namespace cpuemu


#endif//CPUEMU__COMMON__BUS__BUS_MODE_HPP