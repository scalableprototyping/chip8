#pragma once
#ifndef CHIP_8_OPCODES_HPP
#define CHIP_8_OPCODES_HPP

#include <utility>
#include <string>
#include <iostream>
#include <iomanip>

namespace chip8::opcodes
{
    enum class OpCodes : uint8_t
    {
        OpCode_0NNN,
        OpCode_00EE,
        OpCode_00E0,
        OpCode_1NNN,
        OpCode_2NNN,
        OpCode_3XNN,
        OpCode_4XNN,
        OpCode_5XY0,
        OpCode_6XNN,
        OpCode_7XNN,
        OpCode_8XY0,
        OpCode_8XY1,
        OpCode_8XY2,
        OpCode_8XY3,
        OpCode_8XY4,
        OpCode_8XY5,
        OpCode_8XY6,
        OpCode_8XY7,
        OpCode_8XYE,
        OpCode_9XY0,
        OpCode_ANNN,
        OpCode_BNNN,
        OpCode_CXNN,
        OpCode_DXYN,
        OpCode_EX9E,
        OpCode_EXA1,
        OpCode_FX07,
        OpCode_FX0A,
        OpCode_FX15,
        OpCode_FX18,
        OpCode_FX1E,
        OpCode_FX29,
        OpCode_FX33,
        OpCode_FX55,
        OpCode_FX65
    };

    using OpBytes = std::pair<uint8_t, uint8_t>;

}

namespace chip8
{
    inline std::string toStr(const opcodes::OpBytes& _op_bytes)
    {
        std::stringstream ss;
        ss << "0x" 
           << std::setfill('0') << std::setw(2) << std::hex
           << static_cast<int>(_op_bytes.first)
           << std::setfill('0') << std::setw(2) << std::hex
           << static_cast<int>(_op_bytes.second);
        return ss.str();
    }
}

#endif
