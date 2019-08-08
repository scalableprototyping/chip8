#include "Interpreter.hpp"
#include "details/memory.hpp"    // for dumpRomToMemory, initSystemMemory

namespace chip8
{
    Interpreter::Interpreter() :
        display_renderer_       ( pixels_ ),
        sound_timer_            ( [this] () { speaker_.Play(); }, 
                                  [this] () { speaker_.Stop(); } ),
        cpu_cycle_guard_        ( [this] () { InstructionCycle(); },    500_Hz ),
        timers_tick_guard_      ( [this] () { TickTimers(); },          60_Hz  ),
        cpu_task_               ( [this] () { CpuCycle(); }, 1us )
    {
        InitializeRam();
    }

    void Interpreter::LoadRom(std::string_view _rom)
    {
        try
        {
            details::dumpRomToMemory(_rom, program_memory_begin_, ram_.end());
        }
        catch(const std::runtime_error& ex)
        {
            throw Chip8Exception("Error loading rom file ", _rom.data(), ": ", ex.what());
        }
    }

    void Interpreter::StartRom(bool _async)
    {
        program_counter_ = program_memory_begin_;
        cpu_task_.Start(_async);
    }

    void Interpreter::Stop()
    {
        cpu_task_.Stop();
    }

    bool Interpreter::IsRunning() const
    {
        return cpu_task_.IsRunning();
    }

    // Private
    void Interpreter::CpuCycle()
    {
        cpu_cycle_guard_.Execute();
        timers_tick_guard_.Execute();
    }

    void Interpreter::InstructionCycle()
    {
        opcodes::OpBytes op_bytes(*program_counter_, *(std::next(program_counter_)));
        const auto bytes_per_opcode = 2;
        std::advance(program_counter_, bytes_per_opcode);
        ProcessInstruction(op_bytes);

        //TODO: make this optional
        //cout_logger_.Log(op_bytes);
    }

    void Interpreter::InitializeRam()
    {
        details::initSystemMemory(ram_.begin(), interpreter_memory_end_);
    }

    void Interpreter::TickTimers()
    {
        delay_timer_.Tick();
        sound_timer_.Tick();
    }

    void Interpreter::ProcessInstruction(const opcodes::OpBytes& _op_bytes)
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
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x6) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY6>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0x7) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XY7>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x80 && (_op_bytes.second & 0x0F) == 0xE) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_8XYE>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x90 && (_op_bytes.second & 0x0F) == 0x0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_9XY0>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xA0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_ANNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xB0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_BNNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xC0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_CXNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xD0) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_DXYN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xE0 && _op_bytes.second == 0x9E) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_EX9E>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xE0 && _op_bytes.second == 0xA1) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_EXA1>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x07) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX07>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x0A) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX0A>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x15) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX15>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x18) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX18>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x1E) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX1E>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x29) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX29>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x33) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX33>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x55) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX55>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xF0 && _op_bytes.second == 0x65) // NOLINT
        {
            ExecuteInstruction<OpCodes::OpCode_FX65>(_op_bytes); 
        }
        else
        {
            throw OpCodeException(_op_bytes, "Instruction not recognized");
        }
    }
}
