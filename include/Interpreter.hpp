#ifndef CHIP_8_INTERPRETER_HPP
#define CHIP_8_INTERPRETER_HPP

#include <string_view>

#include "memory/Ram.hpp"

namespace chip8
{
    class Interpreter
    {
        public:
            Interpreter();
            ~Interpreter() = default;

            void LoadRom(std::string_view _rom);
            void StartRom();

        private:
            void InitializeRam();

        private:
            memory::Ram ram_;
            memory::RamIter program_counter_;

            const memory::RamIter program_memory_       { ram_.begin() + memory::begin_program_ram };
            const memory::RamIter end_interpter_memory_ { ram_.begin() + memory::interpreter_ram_size };
    };
}
#endif
