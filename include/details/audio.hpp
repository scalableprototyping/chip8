#pragma once
#ifndef CHIP_8_DETAILS_AUDIO_HPP
#define CHIP_8_DETAILS_AUDIO_HPP

#include <stdint.h>  // for int16_t, uint16_t
#include <vector>

namespace chip8::details
{
    std::vector<int16_t> generateToneSamples(double _frequency, uint16_t _sample_rate, double _duration = 1.0);
}

#endif
