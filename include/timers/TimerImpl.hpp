#pragma once
#ifndef CHIP_8_TIMER_IMPL_HPP
#define CHIP_8_TIMER_IMPL_HPP

#include "timers/Timer.hpp"

namespace chip8::timers
{
    template <typename Resolution>
    GeneralizedTimer<Resolution>::GeneralizedTimer(const Callback& _start_callback,
                                                   const Callback& _end_callback) :
        start_callback_ { _start_callback },
        end_callback_   { _end_callback }
    {}

    template <typename Resolution>
    void GeneralizedTimer<Resolution>::Tick()
    {
        if(value_ == 0) { return; }

        value_--;

        //TODO: check for zero or for user-custom value?
        if(value_ == 0 && end_callback_) { end_callback_(); }
    }

    template <typename Resolution>
    void GeneralizedTimer<Resolution>::SetValue(Resolution _value)
    {
        value_ = _value;

        //TODO: does it make sense to let users set the timer to zero?
        if(value_ != 0 && start_callback_) { start_callback_(); }
    }

    template <typename Resolution>
    Resolution GeneralizedTimer<Resolution>::GetValue() const
    {
        return value_;
    }
}

#endif
