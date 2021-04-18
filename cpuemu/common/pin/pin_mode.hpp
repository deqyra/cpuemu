#ifndef CPUEMU__COMMON__PIN__PIN_MODE_HPP
#define CPUEMU__COMMON__PIN__PIN_MODE_HPP

namespace emu
{

enum class PinMode
{
    HiZ = 0x0,
    In  = 0x1,
    Out = 0x2
};

}//namespace emu

#endif//CPUEMU__COMMON__PIN__PIN_MODE_HPP