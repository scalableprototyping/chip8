#include "registers/DataRegister.hpp"

namespace chip8::registers
{
    using Value_t = DataRegister::Value_t;
    using Borrow_t = DataRegister::Borrow_t;
    using MostSignificantBit_t = DataRegister::MostSignificantBit_t;
    using LessSignificantBit_t = DataRegister::LessSignificantBit_t;

    void DataRegister::Set(Value_t _value)
    {
        value_ = _value;
    }

    void DataRegister::Set(const DataRegister& _register)
    {
        value_ = _register.Get();
    }

    Carry_t DataRegister::Add(Value_t _value)
    {
        value_ += _value;
        return value_ < _value;
    }

    Carry_t DataRegister::Add(const DataRegister& _register)
    {
        return Add(_register.Get());
    }

    Borrow_t DataRegister::Subtract(Value_t _value)
    {
        value_ -= _value;
        return value_ > _value;
    }

    Borrow_t DataRegister::Subtract(const DataRegister& _register)
    {
        return Subtract(_register.Get());
    }

    MostSignificantBit_t DataRegister::ShiftLeft()
    {
        auto most_significant_bit = (value_ >> 7) & 0x1;
        value_ <<= 1;

        return most_significant_bit;
    }

    LessSignificantBit_t DataRegister::ShiftRight()
    {
        auto less_significant_bit = value_ & 0x1;
        value_ >>= 1;

        return less_significant_bit;
    }

    Value_t DataRegister::Get() const
    {
        return value_;
    }
}
