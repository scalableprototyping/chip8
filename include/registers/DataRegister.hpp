#ifndef CHIP_8_DATA_REGISTER_HPP
#define CHIP_8_DATA_REGISTER_HPP

#include <array>

namespace chip8::registers
{
    class DataRegister
    {
        public:
            ~DataRegister() = default;

            void Set(uint8_t _value);
            void Set(const DataRegister& _register);

            bool Add(uint8_t _value);
            bool Add(const DataRegister& _register);

            bool Subtract(uint8_t _value);
            bool Subtract(const DataRegister& _register);

            uint8_t ShiftLeft();
            uint8_t ShiftRight();

            uint8_t Get() const;

        private:
            uint8_t value_ {};
    };

    static constexpr uint8_t num_data_registers { 16 };
    using DataRegisters = std::array<DataRegister, num_data_registers>;

}

#endif
