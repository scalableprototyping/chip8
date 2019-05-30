#include "io/Display.hpp"

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    using namespace chip8::io;
    DisplayPixels displayPixels;

    int change = 0; 
    DisplayRenderer displayRenderer(displayPixels);

    while(true) {
        displayRenderer.Update();

        std::cout << "Updating screen \n";
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        switch (++change) {
            case 1:
                displayPixels.Clear();
                displayPixels[0][31] = 1;
                break;
            case 2:
                displayPixels.Clear();
                displayPixels[63][31] = 1;
                break;
            case 3:
                displayPixels.Clear();
                displayPixels[63][0] = 1;
                break;
            default:
                displayPixels.Clear();
                displayPixels[0][0] = 1;
                change = 0;
                break;
        }
    }
}
