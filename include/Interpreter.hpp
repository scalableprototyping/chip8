#ifndef CHIP_8_INTERPRETER_HPP
#define CHIP_8_INTERPRETER_HPP

#include <cstdint>                     // for uint8_t
#include <stdexcept>                   // for runtime_error
#include <string_view>                 // for string_view
#include <vector>                      // for vector

#include "io/display/PixelArray.hpp"   // for PixelArray
#include "io/Keypad.hpp"               // for Keyboard
#include "io/Speaker.hpp"              // for Speaker
#include "memory/Ram.hpp"              // for RamIter, Ram, begin_program_ram
#include "registers/DataRegister.hpp"  // for DataRegisters
#include "registers/IRegister.hpp"     // for IRegister
#include "timers/Timer.hpp"            // for Timer
#include "details/opcodes.hpp"         // for Opcodes
#include "details/exceptions.hpp"      // for Exceptions

namespace chip8::test { class Interpreter; }

namespace chip8
{
    class Interpreter
    {
        public:
            Interpreter();
            ~Interpreter() = default;

            void LoadRom(std::string_view _rom);
            void StartRom();

            void processInstruction(const opcodes::OpBytes& _op_bytes);

        private:
            void InitializeRam();

            template<opcodes::OpCodes> 
            void ExecuteInstruction(const opcodes::OpBytes& _op_byte)
            {
                throw OpCodeException(_op_byte, "Unimplemented opcode function.");
            }

            memory::Ram ram_{};
            memory::RamIter program_counter_{};

            io::display::PixelArray pixels_;
            io::Keypad  keypad_;
            io::Speaker speaker_;

            timers::Timer delay_timer_;
            timers::Timer sound_timer_;

            registers::IRegister i_register_;
            registers::DataRegisters data_registers_;

            const memory::RamIter program_memory_         { ram_.begin() + memory::begin_program_ram };
            const memory::RamIter end_interpreter_memory_ { ram_.begin() + memory::interpreter_ram_size };

            std::vector<memory::RamIter> stack_;

            friend class test::Interpreter;
    };
}

#endif
