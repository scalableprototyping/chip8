#include <chrono>
#include <thread>
#include <gtest/gtest.h>

#include "io/Speaker.hpp"

namespace chip8::test
{
    TEST(Chip8TestSuite, SpeakerDefaultTone)
    {
        io::Speaker speaker;

        ASSERT_FALSE(speaker.IsPlaying());
        speaker.Play();
        ASSERT_TRUE(speaker.IsPlaying());

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(0.3s);

        ASSERT_TRUE(speaker.IsPlaying());
        speaker.Stop();
        ASSERT_FALSE(speaker.IsPlaying());
    }
}
