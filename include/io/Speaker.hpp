#ifndef CHIP_8_SPEAKER_HPP
#define CHIP_8_SPEAKER_HPP

#include <SFML/Audio.hpp>

namespace chip8::io
{
    class Speaker
    {
        public:
            explicit Speaker(double _tone_frequency = 440, uint16_t _sample_rate = 44'100);
            ~Speaker() = default;

            void Play();
            void Stop();

            bool IsPlaying() const { return sound_.getStatus() == sf::SoundSource::Status::Playing; }

        private:
            sf::Sound sound_;
            sf::SoundBuffer sound_buffer_;
    };
}

#endif
