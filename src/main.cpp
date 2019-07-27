#include <cstdint>          // for uint8_t
#include <utility>          // for pair

#include "Interpreter.hpp"  // for Interpreter

int main()
{
    using OpBytes = std::pair<uint8_t, uint8_t>;

    chip8::Interpreter interpreter{};

    OpBytes op{0x00, 0xEE}; // NOLINT
    interpreter.processInstruction(op);
}
