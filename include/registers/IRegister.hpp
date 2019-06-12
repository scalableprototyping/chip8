#ifndef CHIP_8_I_REGISTER_HPP
#define CHIP_8_I_REGISTER_HPP

#include "registers/DataRegister.hpp"

namespace chip8::registers
{
    class IRegister
    {
        public:
            using Value_t = uint16_t;

            ~IRegister() = default;

            void Set(Value_t _value);
            void Add(const DataRegister& _register);

            Value_t Get() const;

        private:
            Value_t value_ {};
    };
}

#endif
