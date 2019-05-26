#include "Interpreter.hpp"
#include "utils/rom.hpp"

namespace chip8
{
    Interpreter::Interpreter()
    {
        InitializeRam();
    }

    void Interpreter::LoadRom(std::string_view _rom)
    {
        try
        {
            utils::dumpRomToMemory(_rom, program_memory_, ram_.end());
        }
        catch(const std::runtime_error& ex)
        {
            throw std::runtime_error { std::string{ "Error loading rom file " } + _rom.data() + ": " + ex.what() };
        }
    }

    void Interpreter::StartRom()
    {
        program_counter_ = ram_.begin();
        //TODO: parse commands
    }

    //Private
    void Interpreter::InitializeRam()
    {
        //TODO: initialize interpreter memory
    }
}
