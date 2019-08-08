#pragma once
#ifndef CHIP_8_CLOCK_HPP
#define CHIP_8_CLOCK_HPP

#include <chrono>

namespace chip8::timers
{
    using namespace std::literals::chrono_literals;

    using Clock        = std::chrono::high_resolution_clock;
    using Milliseconds = std::chrono::milliseconds;
    using Microseconds = std::chrono::microseconds;

    template<class Unit>
    Unit getDuration(const Clock::time_point& _before, const Clock::time_point& _after)
    {
        return std::chrono::duration_cast<Unit>(_after - _before);
    }

    template<class F, class RV = Microseconds>
    RV measureExecutionTime(F _function)
    {
        const auto& before = Clock::now();
        _function();
        const auto& after = Clock::now();

        return getDuration<RV>(before, after);
    }
}

#endif
