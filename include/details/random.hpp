#ifndef CHIP_8_DETAILS_RANDOM_HPP
#define CHIP_8_DETAILS_RANDOM_HPP

#include <random>

namespace chip8::details
{
    template<typename T>
    using UniformDistribution = std::conditional_t<std::is_integral<T>::value, std::uniform_int_distribution<T>,
                                std::conditional_t<std::is_floating_point<T>::value, std::uniform_real_distribution<T>,
                                void>>;

    template<typename T>
    T getRandomNumber(T _min = std::numeric_limits<T>::min(), T _max = std::numeric_limits<T>::max())
    {
        std::mt19937           generator(std::random_device{}());
        UniformDistribution<T> distribution(_min, _max);

        return distribution(generator);
    }

    inline uint8_t getRandomNumber(uint8_t _mask)
    {
        return getRandomNumber<uint8_t>() & _mask;
    }
}

#endif

