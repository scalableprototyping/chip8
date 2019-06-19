#include <gtest/gtest.h>

#include "details/random.hpp"

#include <set>

namespace chip8::test
{
    TEST(Chip8TestSuite, RandomUtilities)
    {
        std::set<size_t> random_numbers;

        for(int i = 1; i < 100; i++)
        {
            random_numbers.insert(details::getRandomNumber<size_t>());
            ASSERT_EQ(random_numbers.size(), i);
        }

        random_numbers.clear();
        uint8_t mask = 0xF;

        for(int i = 1; i < 100; i++)
        {
            uint8_t random_number = details::getRandomNumber(mask);
            ASSERT_LE(random_number, mask);
        }
    }
}
