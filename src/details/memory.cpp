
#include "details/memory.hpp"

#include <algorithm>  // for copy
#include <array>      // for array<>::const_iterator, array
#include <cstddef>    // for size_t
#include <cstdint>    // for uint8_t
#include <fstream>    // for ifstream, ios, operator|, basic_istream, basic_...
#include <iterator>   // for distance, operator!=, istreambuf_iterator
#include <stdexcept>  // for runtime_error
#include <string>     // for char_traits<>::pos_type

namespace chip8::details
{
    void dumpRomToMemory(std::string_view _rom, memory::RamIter _begin, memory::RamIter _end)
    {
        std::ifstream rom_file (_rom.data(), std::ios::binary | std::ios::ate);

        if(!rom_file.is_open()) { throw std::runtime_error { "Cannot open rom file" }; }

        const size_t rom_size = rom_file.tellg();
        const size_t ram_size = std::distance(_begin, _end);

        //TODO: use custom-defined exceptions?
        if(rom_size > ram_size) { throw std::runtime_error { "Rom size exceeds memory" }; }

        rom_file.seekg(0, std::ios::beg);

        using BufferIterator = std::istreambuf_iterator<char>;
        std::copy(BufferIterator(rom_file), BufferIterator(), _begin);
    }

    void initSystemMemory(memory::RamIter _begin, memory::RamIter _end)
    {
        //16 basic sprites. Each 5 bytes long
        static constexpr size_t used_system_memory { (0xF + 1) * 5 };
        static constexpr std::array<uint8_t, used_system_memory> default_sprites
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80, // F
        };

        const size_t system_memory_size = std::distance(_begin, _end);

        if(used_system_memory > system_memory_size) { throw std::runtime_error { "Interpreter memory too small to initialize" }; }

        std::copy(default_sprites.cbegin(), default_sprites.cend(), _begin);
    }
}
