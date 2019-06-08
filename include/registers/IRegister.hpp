#ifndef CHIP_8_I_REGISTER_HPP
#define CHIP_8_I_REGISTER_HPP

#include "registers/DataRegister.hpp"

namespace chip8::registers
{
    class IRegister
    {
        public:
            ~IRegister() = default;

            void Set(uint16_t _value);
            void Add(const DataRegister& _register);

            uint16_t Get() const;

        private:
            uint16_t value_ {};
    };
}

#endif
