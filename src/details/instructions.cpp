#include <cassert>
#include <array>

#include "Interpreter.hpp"
#include "details/instructions.hpp"

namespace chip8::details
{
    static uint8_t getInstructionType(uint8_t _first_byte)
    {
        return (_first_byte >> 4) & 0xF;
    }

    Instruction parseInstruction(const OpBytes& _op_bytes, Interpreter& _interpreter)
    {
        using DispatchFunction = std::function<void(Interpreter&, const OpBytes&)>;

        static constexpr uint8_t num_intruction_types { 16 };
        static const std::array<DispatchFunction, num_intruction_types> dispatch_table
        {
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x0>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x1>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x2>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x3>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x4>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x5>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x6>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x7>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x8>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0x9>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xA>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xB>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xC>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xD>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xE>(_op_bytes); },
            [] (Interpreter& _interpreter, const OpBytes& _op_bytes) { _interpreter.ExecuteInstruction<0xF>(_op_bytes); }
        };

        const uint8_t instruction_type = getInstructionType(_op_bytes.first);
        assert(instruction_type <= dispatch_table.size());

        return [&] () { dispatch_table[instruction_type](_interpreter, _op_bytes); };
    }
}
