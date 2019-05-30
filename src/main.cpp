#include "io/Display.hpp"

#include <iostream>

int main()
{
    using namespace chip8::io;
    DisplayPixels displayPixels;
    DisplayRenderer displayRenderer(displayPixels);
    
    while(true) {
        displayRenderer.Update();
    }
}
