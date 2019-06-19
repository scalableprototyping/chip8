#include "Interpreter.hpp"

#include <stdexcept>             // for runtime_error
#include <string>                // for allocator, operator+, char_traits

#include "details/memory.hpp"
#include "timers/TimerImpl.hpp"  // for GeneralizedTimer::GeneralizedTimer<R...

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
            details::dumpRomToMemory(_rom, program_memory_, ram_.end());
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
        //TODO: tick timers
    }

    //Private
    void Interpreter::InitializeRam()
    {
        details::initSystemMemory(ram_.begin(), end_interpreter_memory_);
    }
}
