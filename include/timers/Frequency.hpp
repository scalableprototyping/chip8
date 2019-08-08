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
                const auto period = static_cast<unsigned long>((1.0e6) / (1.0 * hertz));
                return std::chrono::microseconds(period);
            }

        private:
            uint64_t hertz;
    };

    constexpr chip8::timers::Frequency operator"" _Hz(unsigned long long int hz)
    {
        return chip8::timers::Frequency { hz };
    }

    constexpr chip8::timers::Frequency operator"" _kHz(unsigned long long int khz)
    {
        const int kilo = 1e3;
        return chip8::timers::Frequency { khz * kilo };
    }

    constexpr chip8::timers::Frequency operator"" _MHz(unsigned long long int mhz)
    {
        const int mega = 1e6;
        return chip8::timers::Frequency { mhz * mega };
    }

    constexpr chip8::timers::Frequency operator"" _GHz(unsigned long long int ghz)
    {
        const int giga = 1e9;
        return chip8::timers::Frequency { ghz * giga };
    }

    static constexpr Frequency default_cpu_frequency    { 500_Hz };
    static constexpr Frequency default_timers_frequency { 60_Hz };
}



#endif

