#include <iostream>

#include "Interpreter.hpp"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "Missing rom file. Usage: " << argv[0] << " /path/to/rom." << std::endl;
        return -1;
    }

    chip8::Interpreter chip8_interpreter;

    try
    {
        chip8_interpreter.LoadRom(argv[1]);
        chip8_interpreter.StartRom();
    }
    catch(const std::runtime_error& ex)
    {
        std::cerr << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
