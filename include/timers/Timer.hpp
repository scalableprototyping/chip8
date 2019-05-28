#ifndef CHIP_8_TIMER_HPP
#define CHIP_8_TIMER_HPP

#include <functional>

namespace chip8::timers
{
    using Callback = std::function<void()>;

    template <typename Resolution>
    class GeneralizedTimer
    {
        static_assert(std::is_integral<Resolution>::value, "Timer<T> expects an integral value as resolution");

        public:
            GeneralizedTimer(const Callback& _start_callback = {}, const Callback& _end_callback = {});
            ~GeneralizedTimer() = default;

            void Tick();
            void SetValue(Resolution _value);

            Resolution GetValue() const;

        private:
            Resolution value_ {};

            const Callback start_callback_;
            const Callback end_callback_;
    };

    using Timer = GeneralizedTimer<uint8_t>;
}

#include "timers/TimerImpl.hpp"

#endif
