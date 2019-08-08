#pragma once
#ifndef CHIP_8_RATE_GUARD_HPP
#define CHIP_8_RATE_GUARD_HPP

#include <functional>

#include "timers/clock.hpp"
#include "timers/Frequency.hpp"

namespace chip8::timers
{
    class RateGuard final
    {
        private:
            using Function = std::function<void()>;

        public:
            RateGuard(Function _function, Frequency _desired_frequency) :
                function_  ( _function ),
                frequency_ (_desired_frequency)
            {}
            ~RateGuard() = default;

            void Execute()
            {
                const auto& now = Clock::now();
                const auto& elapsed_time = getDuration<Microseconds>(last_executed_, now);

                if(elapsed_time >= frequency_.Period<Microseconds>())
                {
                    function_();
                    last_executed_ = now;
                }
            };

        private:
            Clock::time_point last_executed_ {};

            const Function  function_;
            const Frequency frequency_;
    };
}

#endif

