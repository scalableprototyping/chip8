#include "io/display/PixelArray.hpp"
#include "io/display/Renderer.hpp"

#include "details/display.hpp"

#include <chrono>
#include <thread>
#include <algorithm>
#include <iostream>

int main()
{
    chip8::io::display::PixelArray pixels;
    chip8::io::display::Renderer displayRenderer(pixels);

    int change = 0; 

    while(true) {
        displayRenderer.Update();

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        std::cout << "Updating Screen\n";
        switch (++change) {
            case 1:
                {
                    pixels.Clear();
                    pixels.at(0,31) = 1;

                    std::vector<int> sprite{
                        0xF0,
                        0x90,
                        0xF0,
                        0x90,
                        0x90
                    };
                    std::for_each(sprite.begin(), sprite.end(), [&, i=0](auto spriteRow) mutable {
                        const auto startRow = 15;
                        const auto startCol = 15;
                        auto pixel = pixels.iterator_at(startCol, startRow + i++);
                        chip8::details::forEachBitInByte(spriteRow, [&](auto bit) {
                            *pixel = bit;
                            ++pixel;
                        });
                    });

                    break;
                }
            case 2:
                pixels.Clear();
                pixels.at(63,31) = 1;
                break;
            case 3:
                pixels.Clear();
                pixels.at(63,0) = 1;
                break;
            default:
                pixels.Clear();
                pixels.at(0,0) = 1;
                change = 0;
                break;
        }
    }
}
