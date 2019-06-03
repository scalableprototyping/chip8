#include <cstdint>
#include <chrono>
#include <thread>

#include <stdexcept>

#include <gtest/gtest.h>

#include "io/display/PixelArray.hpp"
#include "io/display/Renderer.hpp"

#include <iostream>

namespace chip8::test
{
    void expect_cleared_display(const chip8::io::display::PixelArray& pixels)
    {
        for (const auto& pixel : pixels)
        {
            EXPECT_TRUE(pixel == 0);
        }
    }

    TEST(Chip8TestSuite, DisplayColumnOutOfRange) 
    {
        chip8::io::display::PixelArray pixels;
        EXPECT_THROW(pixels.at(64,0) = 1, std::out_of_range);
        EXPECT_THROW(pixels.at(200,0) = 1, std::out_of_range);
    }

    TEST(Chip8TestSuite, DisplayRowOutOfRange) 
    {
        chip8::io::display::PixelArray pixels;
        EXPECT_THROW(pixels.at(0,32) = 1, std::out_of_range);
        EXPECT_THROW(pixels.at(0,200) = 1, std::out_of_range);
    }

    TEST(Chip8TestSuite, DisplayRendering)
    {
        chip8::io::display::PixelArray pixels;
        expect_cleared_display(pixels);

        pixels.at(15,30) = 1;
        for (auto pixelIterator = pixels.begin(); pixelIterator != pixels.end(); ++pixelIterator)
        {
            if (pixelIterator != pixels.iterator_at(15,30))
            {
                EXPECT_TRUE(*pixelIterator == 0);
            }
            else
            {
                EXPECT_TRUE(*pixelIterator == 1);
            }
        }

        pixels.Clear();
        expect_cleared_display(pixels);

        chip8::io::display::Renderer displayRenderer(pixels);
        for (std::size_t i = 0; i < pixels.kHeight_; ++i) 
        {
            std::cout << "i: " << i << "\n";
            pixels.Clear();
            pixels.at(i,i) = 1;
            displayRenderer.Update();
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(0.01s);
        }

    }
}
