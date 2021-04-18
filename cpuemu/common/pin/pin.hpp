#ifndef CPUEMU__COMMON__PIN__PIN_HPP
#define CPUEMU__COMMON__PIN__PIN_HPP

#include <string>

#include "pin_mode.hpp"
#include "pin_state.hpp"

namespace emu
{
    
struct Pin
{
    const std::string name;
    PinMode mode;
    PinState state;
};

}//namespace emu


#endif//CPUEMU__COMMON__PIN__PIN_HPP