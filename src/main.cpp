#include <cstdint>          // for uint8_t
#include <utility>          // for pair

#include "Interpreter.hpp"  // for Interpreter
#include "details/opcodes.hpp"

int main()
{
    chip8::Interpreter interpreter{};

    OpBytes op{0x00, 0xEE}; // NOLINT
    interpreter.processInstruction(op);
}
