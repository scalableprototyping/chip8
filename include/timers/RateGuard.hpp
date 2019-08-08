#ifndef CHIP_8_RATE_GUARD_HPP
#define CHIP_8_RATE_GUARD_HPP

#include <functional>
#include <atomic>

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
                frequency_ (_desired_frequency),
                function_  ( _function )
            {}
            ~RateGuard() = default;

            void Execute()
            {
                const auto& now = Clock::now();
                const auto& elapsed_time = getDuration<Microseconds>(last_executed_, now);

                const Frequency current_frequency = frequency_;

                if(elapsed_time >= current_frequency.Period<Microseconds>())
                {
                    function_();
                    last_executed_ = now;
                }
            };

            void SetFrequency(Frequency _new_frequency)
            {
                frequency_ = _new_frequency;
            }

        private:
            Clock::time_point last_executed_ {};

            std::atomic<Frequency> frequency_;
            const Function  function_;
    };
}

#endif

