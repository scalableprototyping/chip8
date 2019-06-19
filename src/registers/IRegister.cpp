#include "registers/IRegister.hpp"

#include "registers/DataRegister.hpp"

namespace chip8::registers
{
    using Value_t = IRegister::Value_t;

    void IRegister::Set(Value_t _value)
    {
        value_ = _value;
    }

    void IRegister::Add(const DataRegister& _register)
    {
        value_ += _register.Get();
    }

    Value_t IRegister::Get() const
    {
        return value_;
    }
}
