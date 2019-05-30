#include <cstdint>
#include <chrono>
#include <thread>
#include <string>
#include <stdexcept>

#include <gtest/gtest.h>

#include "io/Display.hpp"

namespace chip8::test
{
    using namespace chip8::io;
    void assert_cleared_display(DisplayPixels displayPixels)
    {
        for (std::size_t col = 0; col < displayPixels.kWidth_; ++col) 
        {
            for (std::size_t row = 0; row < displayPixels.kHeight_; ++row) 
            {
                ASSERT_TRUE(displayPixels[col][row] == 0);
            }
        }
    }

    TEST(Chip8TestSuite, Display)
    {
        DisplayPixels displayPixels;
        assert_cleared_display(displayPixels);

        displayPixels[15][30] = 1;
        for (std::size_t col = 0; col < displayPixels.kWidth_; ++col) 
        {
            for (std::size_t row = 0; row < displayPixels.kHeight_; ++row) 
            {
                if(col == 15 && row == 30)
                {
                    ASSERT_TRUE(displayPixels[col][row] == 1);
                }
                else
                {
                    ASSERT_TRUE(displayPixels[col][row] == 0);
                }
            }
        }

        displayPixels.Clear();
        assert_cleared_display(displayPixels);

        try 
        {
            displayPixels[200][200] = 5;
            FAIL() << "Accessing out of bound indeces should throw an std::out_of_range exception\n";
        } 
        catch (std::out_of_range& e) 
        {
            EXPECT_TRUE(std::string(e.what()) == std::string("Trying to access display pixel index out of range."));
        }
        catch (...) 
        {
            FAIL() << "Accessing out of bound indeces should throw an std::out_of_range exception\n";
        }


        DisplayRenderer displayRenderer(displayPixels);
        for (std::size_t i = 0; i < displayPixels.kHeight_; ++i) 
        {
            displayPixels.Clear();
            displayPixels[i][i] = 1;
            displayRenderer.Update();
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(0.01s);
        }

    }
}
