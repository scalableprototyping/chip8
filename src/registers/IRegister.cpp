#include "registers/IRegister.hpp"

namespace chip8::registers
{
    void IRegister::Set(uint16_t _value)
    {
        value_ = _value;
    }

    void IRegister::Add(const DataRegister& _register)
    {
        value_ += _register.Get();
    }

    uint16_t IRegister::Get() const
    {
        return value_;
    }
}
