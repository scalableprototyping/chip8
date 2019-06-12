#include "Interpreter.hpp"
#include "details/instructions.hpp"

namespace chip8::details
{
    void parseInstruction(const OpBytes& _op_bytes, Interpreter& _interpreter)
    {
        if ((_op_bytes.first & 0xF0) == 0x00) 
        {
            ExecuteInstruction<OpCode_0NNN>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xE0)
        {
            ExecuteInstruction<OpCode_00E0>(_op_bytes); 
        }
        else if (_op_bytes.first == 0x00 && _op_bytes.second == 0xEE)
        {
            ExecuteInstruction<OpCode_00EE>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x10)
        {
            ExecuteInstruction<OpCode_1NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0x20)
        {
            ExecuteInstruction<OpCode_2NNN>(_op_bytes); 
        }
        else if ((_op_bytes.first & 0xF0) == 0xD0)
        {
            ExecuteInstruction<OpCode_DXYN>(_op_bytes); 
        }
    }
}
