#ifndef CPUEMU__COMMON__PIN__PIN_STATE_HPP
#define CPUEMU__COMMON__PIN__PIN_STATE_HPP

namespace emu
{

enum class PinState
{
    Low     =  0,
    High    =  1,
    HiZ     = -1
};

}//namespace emu

#endif//CPUEMU__COMMON__PIN__PIN_STATE_HPP