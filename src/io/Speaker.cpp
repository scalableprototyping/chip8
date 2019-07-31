#include "io/Speaker.hpp"

#include "details/audio.hpp"

#include <stdexcept>  // for runtime_error
#include <vector>     // for vector

namespace chip8::io
{
    Speaker::Speaker(double _tone_frequency, uint16_t _sample_rate)
    {
        const auto& tone_samples = details::generateToneSamples(_tone_frequency, _sample_rate);

        if(!sound_buffer_.loadFromSamples(tone_samples.data(), tone_samples.size(), 1, _sample_rate))
        {
            throw std::runtime_error { "Speaker: error loading tone samples" };
        }

        sound_.setBuffer(sound_buffer_);
        sound_.setLoop(true);
    }

    void Speaker::Play()
    {
        sound_.play();
    }

    void Speaker::Stop()
    {
        sound_.stop();
    }
}
