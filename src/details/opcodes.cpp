#include "Interpreter.hpp"

namespace chip8
{
    template<>
    void Interpreter::ExecuteInstruction<0x0>(const details::OpBytes& _op_bytes)
    {
        //if(_op_bytes.first == 0x00 && _op_bytes.second == 0xE0) { display.clean(); };
        //else { throw std::runtime_error { "Error executing instruction"}; }
    }

    /**
    * OpCode 0NNN 
    * Jump to a machine code routine at nnn. This instruction is only used on the old computers on which Chip-8
    * was originally implemented. It is ignored by modern interpreters. This will not be implemented.
    */
    template<>
    void Interpreter::ExecuteInstruction<"0NNN">()
    {
        throw std::runtime_error{"0NNN instruction not implemented. ROM not supported."};
    }

    /**
    * OpCode 00E0 
    * Clear the pixel frame buffer.
    */
    template<>
    void Interpreter::ExecuteInstruction<"00E0">()
    {
        pixels_.Clear();
    }

    /**
    * OpCode 00EE
    * Return from a subrutine.
    */
    template<>
    void Interpreter::ExecuteInstruction<"00EE">(const details::OpBytes& _op_bytes)
    {
        program_counter_ = stack_.back();
        stack_.pop_back();
    }

    /**
    * OpCode 1NNN
    * Jump to address NNN.
    */
    template<>
    void Interpreter::ExecuteInstruction<"1NNN">(uint16_t _nnn)
    {
        program_counter_ = ram_.begin() + _nnn;
    }

    /**
    * OpCode 2NNN 
    * Execute subroutine starting at address NNN
    */
    template<>
    void Interpreter::ExecuteInstruction<"2NNN">(uint16_t _nnn)
    {
        stack_.push_back(program_counter_);
        program_counter_ = ram_.begin() + _nnn;
    }

    /**
    * OpCode DXYN 
    * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address 
    * stored in I Set VF to 01 if any set pixels are changed to unset, and 00 otherwise.
    */
    template<>
    void Interpreter::ExecuteInstruction<"DXYN">(uint8_t _x, uint8_t _y, uint16_t _n)
    {
        for (auto byte_index = 0; byte_index < _n; ++byte_index)
        {
            auto byte = program_memory_.at(index_register_ + byte_index);
            pixels_.WriteByteAt(_x, _y + byte_index, byte);
        }
        // TODO: Set VF register appropiately! 
    }

    /**
    * OpCode ANNN 
    * Store memory address NNN in register I
    */
    template<>
    void Interpreter::ExecuteInstruction<"ANNN">(uint16_t _nnn)
    {
        index_register_ = _nnn;
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
