#pragma once
#ifndef CHIP_8_FREQUENCY_HPP
#define CHIP_8_FREQUENCY_HPP

#include <functional>
#include <chrono>
#include <iostream>

namespace chip8::timers
{
    class Frequency final
    {
        public:
            explicit constexpr Frequency(uint64_t h) : hertz(h) {};

            template<class Unit>
            constexpr Unit Period() const
            {
                const auto period = static_cast<unsigned long>((1000000) / (1.0 * hertz));
                return std::chrono::microseconds(period);
            }

        private:
            uint64_t hertz;
    };

}

constexpr chip8::timers::Frequency operator"" _Hz(unsigned long long int hz)
{
    return chip8::timers::Frequency { hz };
}

constexpr chip8::timers::Frequency operator"" _kHz(unsigned long long int khz)
{
    return chip8::timers::Frequency { khz * 1000 };
}

constexpr chip8::timers::Frequency operator"" _MHz(unsigned long long int mhz)
{
    return chip8::timers::Frequency { mhz * 1000000 };
}

constexpr chip8::timers::Frequency operator"" _GHz(unsigned long long int ghz)
{
    return chip8::timers::Frequency { ghz * 1000000000 };
}

#endif

