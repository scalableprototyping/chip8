#ifndef CHIP_8_RAM_HPP
#define CHIP_8_RAM_HPP

#include <array>

namespace chip8::memory
{
    constexpr uint16_t system_ram_size      { 4096 };
    constexpr uint16_t interpreter_ram_size { 512 };

    using Ram = std::array<uint8_t, system_ram_size>;

    using RamIter      = Ram::iterator;
    using RamConstIter = Ram::const_iterator;

    #ifdef ETI_660
    constexpr uint16_t begin_program_ram { 1536 };
    #else
    constexpr uint16_t begin_program_ram { 512 };
    #endif
}

#endif
