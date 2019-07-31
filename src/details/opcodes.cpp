#include "Interpreter.hpp"
#include "details/opcodes.hpp" // for Opcodes
#include "details/random.hpp"  // for getRandomNumber(mask)

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
        if (stack_.empty())
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
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF); // NOLINT
        program_counter_ = ram_.begin() + nnn;
    }

    /**
    * OpCode 2NNN 
    * Execute subroutine starting at address NNN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_2NNN>(const OpBytes& _op_bytes)
    {
        auto nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF); // NOLINT
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
        const uint8_t register_id = _op_bytes.first & 0x0F; // NOLINT

        if(data_registers_[register_id].Get() == _op_bytes.second) { std::advance(program_counter_, 2); } // NOLINT
    }

    /**
    * OpCode 4XNN 
    * Skip the following instruction if the value of register VX is not equal to NN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_4XNN>(const OpBytes& _op_bytes)
    {
        const uint8_t register_id = _op_bytes.first & 0x0F; // NOLINT

        if(data_registers_[register_id].Get() != _op_bytes.second) { std::advance(program_counter_, 2); } // NOLINT
    }

    /**
    * OpCode 5XY0 
    * Skip the following instruction if the value of register VX is equal to the value of VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_5XY0>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        if(data_registers_[vx].Get() == data_registers_[vy].Get()) { std::advance(program_counter_, 2); } // NOLINT
    }

    /**
    * OpCode 6XNN 
    * Store number NN in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_6XNN>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT

        data_registers_[vx].Set(_op_bytes.second);
    }
    
    /**
    * OpCode 7XNN 
    * Add the value NN in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_7XNN>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT

        data_registers_[vx].Add(_op_bytes.second);
    }

    /**
    * OpCode 8XY0 
    * Store the value of register VY in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY0>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        data_registers_[vx].Set(data_registers_[vy]);
    }

    /**
    * OpCode 8XY1 
    * Set VX to VX OR VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY1>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const uint8_t result = data_registers_[vx].Get() | data_registers_[vy].Get();
        data_registers_[vx].Set(result);
    }

    /**
    * OpCode 8XY2 
    * Set VX to VX AND VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY2>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const uint8_t result = data_registers_[vx].Get() & data_registers_[vy].Get();
        data_registers_[vx].Set(result);
    }

    /**
    * OpCode 8XY3 
    * Set VX to VX XOR VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY3>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const uint8_t result = data_registers_[vx].Get() ^ data_registers_[vy].Get();
        data_registers_[vx].Set(result);
    }

    /**
    * OpCode 8XY4 
    * Add the value of register VY to register VX with carry
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY4>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const bool carry = data_registers_[vx].Add(data_registers_[vy]);
        data_registers_[0xF].Set(static_cast<uint8_t>(carry)); // NOLINT
    }

    /**
    * OpCode 8XY5 
    * Subtract the value of register VY to register VX with carry
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY5>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const bool carry = data_registers_[vx].Subtract(data_registers_[vy]);
        data_registers_[0xF].Set(static_cast<uint8_t>(!carry)); // NOLINT
    }

    /**
    * OpCode 8XY6 
    * Store the value of register VY shifted right one bit in register VX.
    * Set register VF to the least significant bit prior to the shift
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY6>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        data_registers_[vx].Set(data_registers_[vy]);
        const uint8_t less_significant = data_registers_[vx].ShiftRight();

        data_registers_[0xF].Set(less_significant); // NOLINT
    }

    /**
    * OpCode 8XY7 
    * Set register VX to the value of VY minus VX. Set VF to carry value
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XY7>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        const uint8_t previous_value = data_registers_[vx].Get();
        data_registers_[vx].Set(data_registers_[vy]);

        const bool carry = data_registers_[vx].Subtract(previous_value);

        data_registers_[0xF].Set(static_cast<uint8_t>(!carry)); // NOLINT
    }

    /**
    * OpCode 8XYE 
    * Store the value of register VY shifted left one bit in register VX.
    * Set register VF to the most significant bit prior to the shift.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_8XYE>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        data_registers_[vx].Set(data_registers_[vy]);
        const uint8_t most_significant = data_registers_[vx].ShiftLeft();

        data_registers_[0xF].Set(most_significant); // NOLINT
    }

    /**
    * OpCode 9XY0 
    * Skip the following instruction if the value of register VX is not equal to the value of VY
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_9XY0>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint8_t vy = (_op_bytes.second >> 4) & 0x0F; // NOLINT

        if(data_registers_[vx].Get() != data_registers_[vy].Get()) { std::advance(program_counter_, 2); } // NOLINT
    }

    /**
    * OpCode ANNN 
    * Store memory address NNN in register I
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_ANNN>(const OpBytes& _op_bytes)
    {
        uint16_t nnn = (_op_bytes.first & 0x0F) << 8 | _op_bytes.second; // NOLINT
        i_register_.Set(nnn);
    }

    /**
    * OpCode BNNN
    * Jump to address NNN + V0.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_BNNN>(const OpBytes& _op_bytes)
    {
        const uint16_t nnn = (_op_bytes.first & 0x0F) << 8 | (_op_bytes.second & 0xFF); // NOLINT
        program_counter_ = ram_.begin() + nnn + data_registers_[0].Get(); // NOLINT
    }

    /**
    * OpCode CXNN
    * Set VX to a random number with a mask of NN
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_CXNN>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT

        data_registers_[vx].Set(details::getRandomNumber(_op_bytes.second));
    }

    /**
    * OpCode DXYN 
    * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address 
    * stored in I. Set VF to 1 if any set pixels are changed to unset, and 0 otherwise.
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_DXYN>(const OpBytes& _op_bytes)
    {
        auto x = (_op_bytes.first  & 0x0F); // NOLINT
        auto y = (_op_bytes.second & 0xF0) >> 4; // NOLINT
        auto n = (_op_bytes.second & 0x0F); // NOLINT

        data_registers_[0xF].Set(0); // NOLINT
        for (auto byte_index = 0; byte_index < n; ++byte_index)
        {
            auto y_i = y + byte_index;
            auto byte_i = ram_.at(i_register_.Get() + byte_index);

            bool unset_bit_flat = pixels_.WriteByteAt(x, y_i, byte_i);
            if (unset_bit_flat) 
            {
                data_registers_[0xF].Set(1); // NOLINT
            }
        }
    }

    /**
    * OpCode EX9E
    * Skip the following instruction if the key corresponding to the hex value currently 
    * stored in register VX is pressed
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_EX9E>(const OpBytes& _op_bytes)
    {
        const uint8_t vx        = _op_bytes.first & 0x0F;
        const uint8_t hex_value = data_registers_[vx].Get();

        if(keypad_.IsKeyPressed(hex_value)) { std::advance(program_counter_, 2); }
    }

    /**
    * OpCode EXA1
    * Skip the following instruction if the key corresponding to the hex value currently 
    * stored in register VX is not being pressed
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_EXA1>(const OpBytes& _op_bytes)
    {
        const uint8_t vx        = _op_bytes.first & 0x0F;
        const uint8_t hex_value = data_registers_[vx].Get();

        if(!keypad_.IsKeyPressed(hex_value)) { std::advance(program_counter_, 2); }
    }


    /*
    * OpCode FX07
    * Store the curren value of the delay timer in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX07>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;

        data_registers_[vx].Set(delay_timer_.GetValue());
    }

    /**
    * OpCode FX0A
    * Wait for a keypress and store the result in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX0A>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;

        data_registers_[vx].Set(keypad_.WaitForKey());
    }

    /**
    * OpCode FX15
    * Set the delay timer to the value of register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX15>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;

        delay_timer_.SetValue(data_registers_[vx].Get());
    }

    /**
    * OpCode FX18
    * Set the sound timer to the value of register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX18>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;

        sound_timer_.SetValue(data_registers_[vx].Get());
    }

    /**
    * OpCode FX1E
    * Add the value stored in register VX to register I
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX1E>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F;

        i_register_.Add(data_registers_[vx]);
    }

    /**
    * OpCode FX29
    * Set I to the memory address of the sprite data corresponding to the 
    * hexadecimal digit stored in register VX
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX29>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint16_t rows_per_sprite = 5;
        i_register_.Set(rows_per_sprite*data_registers_[vx].Get());
    }

    /**
    * OpCode FX33
    * Store the binary-coded decimal equivalent of the value stored 
    * in register VX at addresses I, I+1, and I+2
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX33>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        const uint16_t vx_val = data_registers_[vx].Get();

        uint8_t hundredth = vx_val/100; // NOLINT
        uint8_t tenth = (vx_val - 100*hundredth)/10; // NOLINT
        uint8_t unit = (vx_val - 100*hundredth -10*tenth); // NOLINT

        const uint16_t i = i_register_.Get();
        ram_.at(i) = hundredth;
        ram_.at(i+1) = tenth; // NOLINT
        ram_.at(i+2) = unit; // NOLINT
    }

    /**
    * OpCode FX55
    * Store the values of registers V0 to VX inclusive in memory starting at address I
    * I is set to I + X + 1 after operation
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX55>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        for (auto i = 0; i <= vx; ++i) 
        {
            ram_.at(i_register_.Get() + i) = data_registers_[i].Get();
        }
        i_register_.Add(vx + 1);
    }

    /**
    * OpCode FX65
    * Fill registers V0 to VX inclusive with the values stored in memory 
    * starting at address I. I is set to I + X + 1 after operation
    */
    template<>
    void Interpreter::ExecuteInstruction<OpCodes::OpCode_FX65>(const OpBytes& _op_bytes)
    {
        const uint8_t vx = _op_bytes.first & 0x0F; // NOLINT
        for (auto i = 0; i <= vx; ++i) 
        {
            data_registers_[i].Set( 
                    ram_.at(i_register_.Get() + i)
                );
        }
        i_register_.Add(vx + 1);
    }

}
