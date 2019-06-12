#include "Interpreter.hpp"

#include "details/memory.hpp"

#include <sstream>
#include <iomanip>

#include <iostream>

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

        //TODO: when should we stop?
        while(true)
        {
            OpBytes op_bytes(*program_counter_, *(program_counter_ + 1));
            processInstruction(op_bytes);

            delay_timer_.Tick();
            sound_timer_.Tick();
        }
    }

    void Interpreter::InitializeRam()
    {
        details::initSystemMemory(ram_.begin(), end_interpreter_memory_);
    }

    void Interpreter::processInstruction(const OpBytes& _op_bytes)
    {
        if ((_op_bytes.first & 0xF0) == 0x00 && (_op_bytes.second & 0xF0) != 0xE0) 
        {
            ExecuteInstruction<OpCodes::OpCode_0NNN>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xE0)
        {
            ExecuteInstruction<OpCodes::OpCode_00E0>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xEE)
        {
            ExecuteInstruction<OpCodes::OpCode_00EE>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x10)
        {
            ExecuteInstruction<OpCodes::OpCode_1NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x20)
        {
            ExecuteInstruction<OpCodes::OpCode_2NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xD0)
        {
            ExecuteInstruction<OpCodes::OpCode_DXYN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xA0) == 0xA0)
        {
            ExecuteInstruction<OpCodes::OpCode_ANNN>(_op_bytes); 
        }
        else {
            std::stringstream ss;
            ss << "0x" << std::setfill('0') << std::setw(2) << std::hex << 
                int(_op_bytes.first)  << 
                int(_op_bytes.second) <<
                " OpCode instruction not recognized.";
            throw std::runtime_error(ss.str());
        }
    }
}
