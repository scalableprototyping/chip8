#include <gtest/gtest.h>

#include "timers/Timer.hpp"

namespace chip8::test
{
    TEST(Chip8TestSuite, TimerNoCallback)
    {
        timers::Timer timer;
        ASSERT_EQ(timer.GetValue(), 0);

        const uint8_t initial_value { 10 };
        timer.SetValue(initial_value);
        ASSERT_EQ(timer.GetValue(), initial_value);

        for(auto i = initial_value; i > 0; i--)
        {
            timer.Tick();
            ASSERT_EQ(timer.GetValue(), i - 1);
        }

        ASSERT_EQ(timer.GetValue(), 0);
        timer.Tick();
        ASSERT_EQ(timer.GetValue(), 0);
    }

    TEST(Chip8TestSuite, TimerCallback)
    {
        bool timer_flag { false };
        auto set_flag = [&timer_flag] () { timer_flag = !timer_flag; };

        timers::Timer timer { set_flag, set_flag };

        ASSERT_EQ(timer.GetValue(), 0);
        ASSERT_FALSE(timer_flag);

        timer.SetValue(0);
        ASSERT_EQ(timer.GetValue(), 0);
        ASSERT_FALSE(timer_flag);

        const uint8_t initial_value { 10 };
        timer.SetValue(initial_value);
        ASSERT_EQ(timer.GetValue(), initial_value);
        ASSERT_TRUE(timer_flag);

        for(auto i = initial_value; i > 1; i--)
        {
            timer.Tick();
            ASSERT_EQ(timer.GetValue(), i - 1);
            ASSERT_TRUE(timer_flag);
        }

        ASSERT_EQ(timer.GetValue(), 1);
        ASSERT_TRUE(timer_flag);

        timer.Tick();
        ASSERT_EQ(timer.GetValue(), 0);
        ASSERT_FALSE(timer_flag);

        timer.Tick();
        ASSERT_EQ(timer.GetValue(), 0);
        ASSERT_FALSE(timer_flag);
    }
}
