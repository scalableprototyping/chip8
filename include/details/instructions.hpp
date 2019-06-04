#ifndef CHIP_8_DETAILS_INSTRUCTIONS_HPP
#define CHIP_8_DETAILS_INSTRUCTIONS_HPP

#include <utility>
#include <functional>

namespace chip8
{
    class Interpreter;
}

namespace chip8::details
{

    using OpBytes     = std::pair<uint8_t, uint8_t>;
    using Instruction = std::function<void()>;

    Instruction parseInstruction(const OpBytes& _op_bytes, Interpreter& _interpreter);
}

#endif
