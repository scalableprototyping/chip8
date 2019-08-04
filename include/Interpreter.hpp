#ifndef CHIP_8_INTERPRETER_HPP
#define CHIP_8_INTERPRETER_HPP

#include <cstdint>                     // for uint8_t
#include <string_view>                 // for string_view
#include <vector>                      // for vector

#include "io/display/PixelArray.hpp"   // for PixelArray
#include "io/display/Renderer.hpp"
#include "io/Keypad.hpp"               // for Keyboard
#include "io/Speaker.hpp"              // for Speaker
#include "memory/Ram.hpp"              // for RamIter, Ram, begin_program_ram
#include "registers/DataRegister.hpp"  // for DataRegisters
#include "registers/IRegister.hpp"     // for IRegister
#include "timers/Timer.hpp"            // for Timer
#include "timers/RateGuard.hpp"        // for RateGuard
#include "timers/clock.hpp"            // for Frequency, etc
#include "details/opcodes.hpp"         // for Opcodes
#include "details/exceptions.hpp"      // for Exceptions

#include "loggers/CoutLogger.hpp"      // for CoutLogger

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

        private:
            void InitializeRam();
            void ProcessInstruction(const opcodes::OpBytes& _op_bytes);

            void InstructionCycle();
            void TickTimers();
            void RefreshDisplay();

            template<opcodes::OpCodes> 
            void ExecuteInstruction(const opcodes::OpBytes& _op_byte)
            {
                throw OpCodeException(_op_byte, "Unimplemented opcode function.");
            }

        private:
            memory::Ram ram_{};
            memory::RamIter program_counter_{};

            timers::Timer delay_timer_{};
            timers::Timer sound_timer_;
            timers::RateGuard tick_guard_;

            registers::IRegister i_register_{};
            registers::DataRegisters data_registers_{};

            io::display::PixelArray pixels_ {};
            io::display::Renderer display_renderer_;
            bool update_display_ { false };

            io::Keypad  keypad_ {};
            io::Speaker speaker_{};

            const memory::RamIter program_memory_         { ram_.begin() + memory::begin_program_ram };
            const memory::RamIter end_interpreter_memory_ { ram_.begin() + memory::interpreter_ram_size };

            std::vector<memory::RamIter> stack_{};

            log::CoutLogger cout_logger_;
            
            const timers::Frequency cpu_frequency_ { 500_Hz };

            friend class test::Interpreter;
    };
}

#endif
