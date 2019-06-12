#include "Interpreter.hpp"
#include <utility>

int main()
{
    chip8::Interpreter interpreter{};
    using OpBytes = std::pair<uint8_t, uint8_t>;
    OpBytes op;
    op.first = 0x00;
    op.second = 0xEE;
    interpreter.processInstruction(op);
}
