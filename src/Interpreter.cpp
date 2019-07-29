#include "Interpreter.hpp"

#include "details/memory.hpp"    // for dumpRomToMemory, initSystemMemory
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
            throw Chip8Exception("Error loading rom file ", _rom.data(), ": ", ex.what());
        }
    }

    void Interpreter::StartRom()
    {
        program_counter_ = ram_.begin();

        //TODO: when should we stop?
        while(true)
        {
            opcodes::OpBytes op_bytes(*program_counter_, *(program_counter_ + 1));
            processInstruction(op_bytes);

            delay_timer_.Tick();
            sound_timer_.Tick();
        }
    }

    void Interpreter::InitializeRam()
    {
        details::initSystemMemory(ram_.begin(), end_interpreter_memory_);
    }

    void Interpreter::processInstruction(const opcodes::OpBytes& _op_bytes)
    {
        using namespace opcodes;

        if ((_op_bytes.first & 0xF0) == 0x00 && (_op_bytes.second & 0xF0) != 0xE0)  // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_0NNN>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xE0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_00E0>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xEE) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_00EE>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x10) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_1NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x20) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_2NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xD0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_DXYN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xA0) == 0xA0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_ANNN>(_op_bytes); 
        }
        else
        {
            throw OpCodeException(_op_bytes, "Instruction not recognized");
        }
    }
}
