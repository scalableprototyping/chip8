#include <gtest/gtest.h>

#include "registers/DataRegister.hpp"
#include "registers/IRegister.hpp"

namespace chip8::test
{
    TEST(Chip8TestSuite, DataRegister)
    {
        bool overflow { false };

        registers::DataRegister first_register;
        registers::DataRegister second_register;

        ASSERT_EQ(first_register.Get(), 0);

        overflow = first_register.Add(15);
        ASSERT_EQ(first_register.Get(), 15);
        ASSERT_FALSE(overflow);

        second_register.Set(5);
        ASSERT_EQ(second_register.Get(), 5);

        overflow = first_register.Add(second_register);
        ASSERT_EQ(first_register.Get(), 20);
        ASSERT_EQ(second_register.Get(), 5);
        ASSERT_FALSE(overflow);

        first_register.Set(6);
        second_register.Set(250);
        overflow = first_register.Add(second_register);
        ASSERT_TRUE(overflow);

        first_register.Set(249);
        overflow = first_register.Subtract(second_register);
        ASSERT_TRUE(overflow);

        first_register.Set(0x01);
        uint8_t shifted_bit = first_register.ShiftRight();
        ASSERT_EQ(first_register.Get(), 0);
        ASSERT_EQ(shifted_bit, 1);

        first_register.Set(0b10000000);
        shifted_bit = first_register.ShiftLeft();
        ASSERT_EQ(first_register.Get(), 0);
        ASSERT_EQ(shifted_bit, 1);
    }

    TEST(Chip8TestSuite, IRegister)
    {
        registers::IRegister i_register;
        registers::DataRegister data_register;

        ASSERT_EQ(data_register.Get(), 0);
        ASSERT_EQ(i_register.Get(), 0);

        i_register.Set(10);
        ASSERT_EQ(i_register.Get(), 10);

        data_register.Set(20);
        ASSERT_EQ(data_register.Get(), 20);

        i_register.Add(data_register);
        ASSERT_EQ(i_register.Get(), 30);
        ASSERT_EQ(data_register.Get(), 20);
    }
}
