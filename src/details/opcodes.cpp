#include "Interpreter.hpp"

namespace chip8
{
    using Interpreter::Opcodes;

    /**
    * OpCode 0NNN 
    * Jump to a machine code routine at nnn. This instruction is only used on the old computers on which Chip-8
    * was originally implemented. It is ignored by modern interpreters. This will not be implemented.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_0NNN>(const details::OpBytes& _op_bytes)
    {
        throw std::runtime_error{"0NNN instruction not implemented. ROM not supported."};
    }

    /**
    * OpCode 00E0 
    * Clear the pixel frame buffer.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_00E0>(const details::OpBytes& _op_bytes)
    {
        pixels_.Clear();
    }

    /**
    * OpCode 00EE
    * Return from a subrutine.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_00EE>(const details::OpBytes& _op_bytes)
    {
        program_counter_ = stack_.back();
        stack_.pop_back();
    }

    /**
    * OpCode 1NNN
    * Jump to address NNN.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_1NNN>(const details::OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF);
        program_counter_ = ram_.begin() + nnn;
    }

    /**
    * OpCode 2NNN 
    * Execute subroutine starting at address NNN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_2NNN>(const details::OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF);
        stack_.push_back(program_counter_);
        program_counter_ = ram_.begin() + nnn;
    }

    /**
    * OpCode DXYN 
    * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address 
    * stored in I Set VF to 01 if any set pixels are changed to unset, and 00 otherwise.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_DXYN>(const details::OpBytes& _op_bytes)
    {
        auto x = (_op_bytes.first  & 0x0F);
        auto y = (_op_bytes.second & 0xF0) >> 4;
        auto n = (_op_bytes.second & 0x0F);

        for (auto byte_index = 0; byte_index < n; ++byte_index)
        {
            auto byte = program_memory_.at(index_register_ + byte_index);
            pixels_.WriteByteAt(x, y + byte_index, byte);
        }
        // TODO: Set VF register appropiately! 
    }

    /**
    * OpCode ANNN 
    * Store memory address NNN in register I
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCode_ANNN>(const details::OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF);
        index_register_ = nnn;
    }

}
