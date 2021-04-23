#ifndef CPUEMU__W65C02S__STATUS_REGISTER_HPP
#define CPUEMU__W65C02S__STATUS_REGISTER_HPP

namespace emu::w65c02s
{

struct StatusRegister
{
    unsigned char c: 1;  // Carry
    unsigned char z: 1;  // Zero
    unsigned char i: 1;  // Interrupt disable
    unsigned char d: 1;  // Decimal mode
    unsigned char b: 1;  // Break command
    unsigned char u: 1;  // User flag
    unsigned char v: 1;  // Overflow
    unsigned char n: 1;  // Negative
};

}

#endif//CPUEMU__W65C02S__STATUS_REGISTER_HPP