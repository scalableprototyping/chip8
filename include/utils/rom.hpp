#ifndef CHIP_8_UTILS_ROM_HPP
#define CHIP_8_UTILS_ROM_HPP

#include <string_view>

#include "memory/Ram.hpp"

namespace chip8::utils
{
    void dumpRomToMemory(std::string_view _rom, memory::RamIter _begin, memory::RamIter _end);
}

#endif
