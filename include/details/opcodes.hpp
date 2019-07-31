#ifndef CHIP_8_OPCODES_HPP
#define CHIP_8_OPCODES_HPP

#include <utility>

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
        OpCode_DXYN,
        OpCode_EX9E,
        OpCode_EXA1,
        OpCode_ANNN,
        OpCode_BNNN,
        OpCode_CXNN,
        OpCode_FX07,
        OpCode_FX15,
        OpCode_FX18,
        OpCode_FX1E,
    };

    using OpBytes = std::pair<uint8_t, uint8_t>;
}

#endif
