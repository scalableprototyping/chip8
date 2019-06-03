#include "io/display/PixelArray.hpp"
#include "io/display/Renderer.hpp"

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
                pixels.Clear();
                pixels.at(0,31) = 1;
                break;
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
