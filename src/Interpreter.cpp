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

        //TODO: check if the instructions generated by the compiler are the same with if/else and a switch
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
        else if ((_op_bytes.first & 0xF0) == 0x30) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_3XNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x40) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_4XNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x50 && (_op_bytes.second & 0x0F) == 0x0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_5XY0>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x60) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_6XNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x70) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_7XNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY0>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x1) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY1>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x2) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY2>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x3) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY3>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x4) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY4>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x5) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY5>(_op_bytes); 
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
