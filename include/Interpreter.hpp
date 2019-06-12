#ifndef CHIP_8_INTERPRETER_HPP
#define CHIP_8_INTERPRETER_HPP

#include <string_view>

#include "memory/Ram.hpp"
#include "timers/Timer.hpp"
#include "io/display/PixelArray.hpp"

namespace chip8
{
    class Interpreter
    {
        public:
            using OpBytes = std::pair<uint8_t, uint8_t>;

            Interpreter();
            ~Interpreter() = default;

            void LoadRom(std::string_view _rom);
            void StartRom();

            enum OpCodes {
                OpCode_0NNN,
                OpCode_00EE,
                OpCode_00E0,
                OpCode_1NNN,
                OpCode_2NNN,
                OpCode_DXYN,
                OpCode_ANNN
            };

            void processInstruction(const OpBytes& _op_bytes);

        private:
            void InitializeRam();

            template<OpCodes> 
            void ExecuteInstruction(const OpBytes&) {
                throw std::runtime_error("Unimplemented opcode function.");
            }

            memory::Ram ram_;
            memory::RamIter program_counter_;

            timers::Timer delay_timer_;
            //TODO: initialize sound timer callbacks
            timers::Timer sound_timer_;

            const memory::RamIter program_memory_         { ram_.begin() + memory::begin_program_ram };
            const memory::RamIter end_interpreter_memory_ { ram_.begin() + memory::interpreter_ram_size };

            io::display::PixelArray pixels_;

            std::vector<memory::RamIter> stack_;
            //TODO: change with register class
            uint16_t index_register_;
    };
}

#endif
