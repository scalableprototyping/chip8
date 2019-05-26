#include <gtest/gtest.h>

#include "utils/rom.hpp"

namespace chip8::test
{
    TEST(Chip8TestSuite, RomParsing)
    {
        memory::Ram ram_memory;

        //Non-existant rom file
        ASSERT_THROW(utils::dumpRomToMemory("fake.rom", ram_memory.begin() + memory::begin_program_ram,
                    ram_memory.end()), std::runtime_error);

        /*
        ASSERT_NO_THROW(utils::dumpRomToMemory("fake.rom", ram_memory.begin() + memory::begin_program_ram,
                    ram_memory.end()));
                    */
    }
}
