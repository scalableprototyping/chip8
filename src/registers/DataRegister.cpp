#include "registers/DataRegister.hpp"

namespace chip8::registers
{
    void DataRegister::Set(uint8_t _value)
    {
        value_ = _value;
    }

    void DataRegister::Set(const DataRegister& _register)
    {
        value_ = _register.Get();
    }

    bool DataRegister::Add(uint8_t _value)
    {
        value_ += _value;
        return value_ < _value;
    }

    bool DataRegister::Add(const DataRegister& _register)
    {
        return Add(_register.Get());
    }

    bool DataRegister::Substract(uint8_t _value)
    {
        value_ -= _value;
        return value_ > _value;
    }

    bool DataRegister::Substract(const DataRegister& _register)
    {
        return Substract(_register.Get());
    }

    uint8_t DataRegister::ShiftLeft()
    {
        uint8_t most_significant_bit = (value_ >> 7) & 0x1;
        value_ <<= 1;

        return most_significant_bit;
    }

    uint8_t DataRegister::ShiftRight()
    {
        uint8_t less_significant_bit = value_ & 0x1;
        value_ >>= 1;

        return less_significant_bit;
    }

    uint8_t DataRegister::Get() const
    {
        return value_;
    }
}
