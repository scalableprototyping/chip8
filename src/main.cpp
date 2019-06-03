#include "io/display/PixelArray.hpp"
#include "io/display/Renderer.hpp"
#include "io/display/SpriteRow.hpp"

#include <chrono>
#include <thread>

int main()
{
    chip8::io::display::PixelArray pixels;
    chip8::io::display::Renderer displayRenderer(pixels);

    int change = 0; 

    while(true) {
        displayRenderer.Update();

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        switch (++change) {
            case 1:
                {
                    pixels.Clear();
                    pixels.at(0,31) = 1;
                    std::vector<chip8::io::display::SpriteRow> sprite;
                    sprite.emplace_back(0xF0);
                    sprite.emplace_back(0x90);
                    sprite.emplace_back(0xF0);
                    sprite.emplace_back(0x90);
                    sprite.emplace_back(0x90);
                    auto start_at_row = 15;
                    auto start_at_col = 15;
                    for (const auto& spriteRow : sprite)
                    {
                        std::copy(spriteRow.begin(), spriteRow.end(), 
                                  pixels.iterator_at(start_at_col, start_at_row++));
                    }
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
