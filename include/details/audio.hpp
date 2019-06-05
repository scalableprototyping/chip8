#ifndef CHIP_8_DETAILS_AUDIO_HPP
#define CHIP_8_DETAILS_AUDIO_HPP

#include <vector>

#include "io/Speaker.hpp"

namespace chip8::details
{
    std::vector<int16_t> generateToneSamples(double _frequency, uint16_t _sample_rate, double _duration = 1.0);
}

#endif
