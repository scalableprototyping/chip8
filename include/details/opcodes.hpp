#ifndef CHIP_8_OPCODES_HPP
#define CHIP_8_OPCODES_HPP

#include <utility>
#include <string>
#include <iostream>
#include <iomanip>

namespace chip8::opcodes
{
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
