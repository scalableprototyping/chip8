#include <gtest/gtest.h>

#include "details/display.hpp"
#include "io/display/PixelArray.hpp"
#include "io/display/Renderer.hpp"

#include <bitset>
#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <thread>

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

        chip8::details::forEachBitInByteLittleEndian(0b0000'0101, [&](auto bit_index_little_endian, auto bit) {
            pixels.at(15+bit_index_little_endian, 15) = bit;
        });
        EXPECT_TRUE(pixels.at(15,15) == 1);
        EXPECT_TRUE(pixels.at(16,15) == 0);
        EXPECT_TRUE(pixels.at(17,15) == 1);
        EXPECT_TRUE(pixels.at(18,15) == 0);
        EXPECT_TRUE(pixels.at(19,15) == 0);
        EXPECT_TRUE(pixels.at(20,15) == 0);
        EXPECT_TRUE(pixels.at(21,15) == 0);
        EXPECT_TRUE(pixels.at(22,15) == 0);

        pixels.Clear();
        expect_cleared_display(pixels);

        chip8::io::display::Renderer displayRenderer(pixels);
        for (std::size_t i = 0; i < chip8::io::display::PixelArray::kHeight_; ++i) 
        {
            pixels.Clear();
            pixels.at(i,i) = 1;
            displayRenderer.Update();
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(0.01s);
        }

    }
}
