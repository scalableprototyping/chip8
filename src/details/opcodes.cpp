#include "Interpreter.hpp"
#include "details/opcodes.hpp" // for Opcodes

namespace chip8
{
    using namespace opcodes; // NOLINT

    /**
    * OpCode 0NNN 
    * Jump to a machine code routine at nnn. This instruction is only used on the old computers on which Chip-8
    * was originally implemented. It is ignored by modern interpreters. This will not be implemented.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_0NNN>(const OpBytes& _op_bytes)
    {
        throw OpCodeException(_op_bytes, "Instruction not implemented. ROM not supported.");
    }

    /**
    * OpCode 00E0 
    * Clear the pixel frame buffer.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_00E0>(const OpBytes& _op_bytes)
    {
        (void) _op_bytes;
        pixels_.Clear();
    }

    /**
    * OpCode 00EE
    * Return from a subrutine.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_00EE>(const OpBytes& _op_bytes)
    {
        if (stack_.size() == 0)
        {
            throw OpCodeException(_op_bytes, "Empty stack. Cannot return from subroutine");
        }
        program_counter_ = stack_.back();
        stack_.pop_back();
    }

    /**
    * OpCode 1NNN
    * Jump to address NNN.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_1NNN>(const OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF);
        program_counter_ = ram_.begin() + nnn;
    }

    /**
    * OpCode 2NNN 
    * Execute subroutine starting at address NNN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_2NNN>(const OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF);
        stack_.push_back(program_counter_);
        program_counter_ = ram_.begin() + nnn;
    }

    /**
    * OpCode 3XNN 
    * Skip the following instruction if the value of register VX equals NN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_3XNN>(const OpBytes& _op_bytes)
    {
        const uint8_t register_id = _op_bytes.first & 0x0F;

        if(data_registers_[register_id].Get() == _op_bytes.second) { std::advance(program_counter_, 2); }
    }

    /**
    * OpCode 4XNN 
    * Skip the following instruction if the value of register VX is not equal to NN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_4XNN>(const OpBytes& _op_bytes)
    {
        const uint8_t register_id = _op_bytes.first & 0x0F;

        if(data_registers_[register_id].Get() != _op_bytes.second) { std::advance(program_counter_, 2); }
    }

    /**
    * OpCode 5XY0 
    * Skip the following instruction if the value of register VX is equal to the value of VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_5XY0>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F;

        if(data_registers_[vx].Get() == data_registers_[vy].Get()) { std::advance(program_counter_, 2); }
    }

    /**
    * OpCode DXYN 
    * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address 
    * stored in I. Set VF to 1 if any set pixels are changed to unset, and 0 otherwise.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_DXYN>(const OpBytes& _op_bytes)
    {
        auto x = (_op_bytes.first  & 0x0F);
        auto y = (_op_bytes.second & 0xF0) >> 4;
        auto n = (_op_bytes.second & 0x0F);

        data_registers_[0xF].Set(0);
        for (auto byte_index = 0; byte_index < n; ++byte_index)
        {
            auto y_i = y + byte_index;
            auto byte_i = ram_.at(i_register_.Get() + byte_index);

            bool unset_bit_flat = pixels_.WriteByteAt(x, y_i, byte_i);
            if (unset_bit_flat) 
            {
                data_registers_[0xF].Set(1);
            }
        }
    }

    /**
    * OpCode ANNN 
    * Store memory address NNN in register I
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_ANNN>(const OpBytes& _op_bytes)
    {
        uint16_t nnn = (_op_bytes.first & 0x0F) << 8 | _op_bytes.second;
        i_register_.Set(nnn);
    }

}
