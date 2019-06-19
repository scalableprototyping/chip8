#ifndef CHIP_8_DATA_REGISTER_HPP
#define CHIP_8_DATA_REGISTER_HPP

#include <array>
#include <stdint.h>  // for uint8_t

namespace chip8::registers
{
    class DataRegister
    {
        public:
            using Value_t = uint8_t;
            using Carry_t = bool;
            using Borrow_t = bool;
            using MostSignificantBit_t = uint8_t;
            using LessSignificantBit_t = uint8_t;

            ~DataRegister() = default;

            void Set(Value_t _value);
            void Set(const DataRegister& _register);

            Carry_t Add(Value_t _value);
            Carry_t Add(const DataRegister& _register);

            Borrow_t Subtract(Value_t _value);
            Borrow_t Subtract(const DataRegister& _register);

            MostSignificantBit_t ShiftLeft();
            LessSignificantBit_t ShiftRight();

            Value_t Get() const;

        private:
            Value_t value_ {};
    };

    static constexpr int num_data_registers { 16 };
    using DataRegisters = std::array<DataRegister, num_data_registers>;
}

#endif
