#include "Interpreter.hpp"

namespace chip8
{
    template<>
    void Interpreter::ExecuteInstruction<0x0>(const details::OpBytes& _op_bytes)
    {
        //if(_op_bytes.first == 0x00 && _op_bytes.second == 0xE0) { display.clean(); };
        //else { throw std::runtime_error { "Error executing instruction"}; }
    }

    template<>
    void Interpreter::ExecuteInstruction<0x1>(const details::OpBytes& _op_bytes)
    {
        //Jump to address NNN
    }

    template<>
    void Interpreter::ExecuteInstruction<0x2>(const details::OpBytes& _op_bytes)
    {
        //Execute subroutine
    }

    template<>
    void Interpreter::ExecuteInstruction<0x3>(const details::OpBytes& _op_bytes)
    {
        //Skip instruction if VX == NN
    }

    template<>
    void Interpreter::ExecuteInstruction<0x4>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0x5>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0x6>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0x7>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0x8>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0x9>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xA>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xB>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xC>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xD>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xE>(const details::OpBytes& _op_bytes)
    {
    }

    template<>
    void Interpreter::ExecuteInstruction<0xF>(const details::OpBytes& _op_bytes)
    {
    }
}
