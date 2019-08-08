#pragma once
#ifndef CHIP_8_DETAILS_MEMORY_HPP
#define CHIP_8_DETAILS_MEMORY_HPP

#include <string_view>

#include "memory/Ram.hpp"

namespace chip8::details
{
    void dumpRomToMemory(std::string_view _rom, memory::RamIter _begin, memory::RamIter _end);
    void initSystemMemory(memory::RamIter _begin, memory::RamIter _end);
}

#endif
