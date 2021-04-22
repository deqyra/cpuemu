#include "types.hpp"

namespace emu
{

Word<Endianness::Little>::Word()
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = 0x00;
    this->h = 0x00;
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = 0x00;
    this->h = 0x00;
#endif
}

Word<Endianness::Big>::Word()
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = 0x00;
    this->h = 0x00;
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = 0x00;
    this->h = 0x00;
#endif
}

Word<Endianness::Little>::Word(uint16_t v)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = ((Byte*)&v)[0];
    this->h = ((Byte*)&v)[1];
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = ((Byte*)&v)[1];
    this->h = ((Byte*)&v)[0];
#endif
}

Word<Endianness::Big>::Word(uint16_t v)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = ((Byte*)&v)[1];
    this->h = ((Byte*)&v)[0];
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = ((Byte*)&v)[0];
    this->h = ((Byte*)&v)[1];
#endif
}

Word<Endianness::Little>& Word<Endianness::Little>::operator=(uint16_t v)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = ((Byte*)&v)[0];
    this->h = ((Byte*)&v)[1];
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = ((Byte*)&v)[1];
    this->h = ((Byte*)&v)[0];
#endif

    return *this;
}

Word<Endianness::Big>& Word<Endianness::Big>::operator=(uint16_t v)
{
#ifdef SYSTEM_LITTLE_ENDIAN
    this->l = ((Byte*)&v)[1];
    this->h = ((Byte*)&v)[0];
#else // if defined SYSTEM_BIG_ENDIAN
    this->l = ((Byte*)&v)[0];
    this->h = ((Byte*)&v)[1];
#endif

    return *this;
}

Word<Endianness::Little>& Word<Endianness::Little>::operator+(Word<Endianness::Little> w)
{
    uint32_t v = (uint16_t)(*this) + (uint16_t)(w);
    (*this) = (uint16_t)(v);

    return *this;
}

Word<Endianness::Big>& Word<Endianness::Big>::operator+(Word<Endianness::Big> w)
{
    uint32_t v = (uint16_t)(*this) + (uint16_t)(w);
    (*this) = (uint16_t)(v);

    return *this;
}

Word<Endianness::Little>& Word<Endianness::Little>::operator-(Word<Endianness::Little> w)
{
    uint32_t v = (uint16_t)(*this) - (uint16_t)(w);
    (*this) = (uint16_t)(v);

    return *this;
}

Word<Endianness::Big>& Word<Endianness::Big>::operator-(Word<Endianness::Big> w)
{
    uint32_t v = (uint16_t)(*this) - (uint16_t)(w);
    (*this) = (uint16_t)(v);

    return *this;
}

Word<Endianness::Little>& Word<Endianness::Little>::operator++()
{
    (*this) = (uint16_t)((uint16_t)(*this) + 1);

    return *this;
}

Word<Endianness::Big>& Word<Endianness::Big>::operator++()
{
    (*this) = (uint16_t)((uint16_t)(*this) + 1);

    return *this;
}

Word<Endianness::Little> Word<Endianness::Little>::operator++(int)
{
    Word<Endianness::Little> v(*this);
    (*this) = (uint16_t)((uint16_t)(*this) + 1);

    return v;
}

Word<Endianness::Big> Word<Endianness::Big>::operator++(int)
{
    Word<Endianness::Big> v(*this);
    (*this) = (uint16_t)((uint16_t)(*this) + 1);

    return v;
}

Word<Endianness::Little>& Word<Endianness::Little>::operator--()
{
    (*this) = (uint16_t)((uint16_t)(*this) - 1);

    return *this;
}

Word<Endianness::Big>& Word<Endianness::Big>::operator--()
{
    (*this) = (uint16_t)((uint16_t)(*this) - 1);

    return *this;
}

Word<Endianness::Little> Word<Endianness::Little>::operator--(int)
{
    Word<Endianness::Little> v(*this);
    (*this) = (uint16_t)((uint16_t)(*this) - 1);

    return v;
}

Word<Endianness::Big> Word<Endianness::Big>::operator--(int)
{
    Word<Endianness::Big> v(*this);
    (*this) = (uint16_t)((uint16_t)(*this) - 1);

    return v;
}

Word<Endianness::Little>::operator uint16_t()
{
    return (h << 8) + l;
}

Word<Endianness::Big>::operator uint16_t()
{
    return (h << 8) + l;
}

}