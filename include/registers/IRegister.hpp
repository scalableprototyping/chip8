#ifndef CHIP_8_I_REGISTER_HPP
#define CHIP_8_I_REGISTER_HPP

#include <cstdint>  // for uint16_t

namespace chip8::registers { class DataRegister; }

namespace chip8::registers
{
    class IRegister
    {
        public:
            using Value_t = uint16_t;
            using Carry_t = bool;

            ~IRegister() = default;

            void Set(Value_t _value);
            Carry_t Add(Value_t _value);
            void Add(const DataRegister& _register);

            Value_t Get() const;

        private:
            Value_t value_ {};
    };
}

#endif
