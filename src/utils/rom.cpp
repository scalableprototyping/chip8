#include <algorithm>
#include <fstream>

#include "utils/rom.hpp"

namespace chip8::utils
{
    void dumpRomToMemory(std::string_view _rom, memory::RamIter _begin, memory::RamIter _end)
    {
        std::ifstream rom_file (_rom.data(), std::ios::binary | std::ios::ate);

        if(!rom_file.is_open()) { throw std::runtime_error { "Cannot open rom file" }; }

        const auto rom_size = rom_file.tellg();
        const auto ram_size = std::distance(_begin, _end);

        //TODO: use custom-defined exceptions?
        if(rom_size > ram_size) { throw std::runtime_error { "Rom size exceeds memory" }; }

        rom_file.seekg(0, std::ios::beg);

        using BufferIterator = std::istreambuf_iterator<char>;
        std::copy(BufferIterator(rom_file), BufferIterator(), _begin);

        return;
    }
}
