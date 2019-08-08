#include <iostream>

#include "Interpreter.hpp"  // for Interpreter

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "/path/to/rom" << std::endl;
        return -1;
    }

    try
    {
        chip8::Interpreter interpreter {};
        interpreter.LoadRom(argv[1]);
        interpreter.StartRom();
    }
    catch(const chip8::Chip8Exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
