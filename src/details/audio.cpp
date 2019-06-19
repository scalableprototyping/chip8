#include "details/audio.hpp"

#include <algorithm>  // for generate
#include <cmath>
#include <cstddef>   // for size_t
#include <cstdint>   // for int16_t, uint16_t

namespace chip8::details
{
    std::vector<int16_t> generateToneSamples(double _frequency, uint16_t _sample_rate, double _duration)
    {
        static constexpr uint16_t amplitude   { 30000 };

        const size_t num_samples = _sample_rate * _duration;
        const double increment   = _frequency / (1.0 * _sample_rate);
        double step = 0;

        auto generator = [&] ()
        { 
            double value = amplitude * std::sin(step * 2 * M_PI);
            step += increment;
            return value;
        };

        std::vector<int16_t> samples (num_samples);
        std::generate(samples.begin(), samples.end(), generator);

        return samples;
    }
}
