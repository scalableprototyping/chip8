#ifndef CHIP_8_INTERPRETER_HPP
#define CHIP_8_INTERPRETER_HPP

#include <cstdint>                      // for uint8_t
#include <string_view>                  // for string_view
#include <vector>                       // for vector

#include "io/display/PixelArray.hpp"    // for PixelArray
#include "io/display/DisplayRenderingPolicySfml.hpp"
#include "io/Keypad.hpp"                // for Keyboard
#include "io/Speaker.hpp"               // for Speaker
#include "memory/Ram.hpp"               // for RamIter, Ram, begin_program_ram
#include "registers/DataRegister.hpp"   // for DataRegisters
#include "registers/IRegister.hpp"      // for IRegister
#include "timers/Timer.hpp"             // for Timer
#include "timers/RateGuard.hpp"         // for RateGuard
#include "timers/clock.hpp"             // for Frequency, etc
#include "details/opcodes.hpp"          // for Opcodes
#include "details/exceptions.hpp"       // for Exceptions
#include "tasks/RecurrentTask.hpp"      // for RecurrentTask

#include "loggers/CoutLogger.hpp"       // for CoutLogger

namespace chip8::test { class Interpreter; }

namespace chip8
{
        //TODO: add void_t concept to make sure it has the methods required
    template
    <
        class DisplayRenderingPolicy = io::display::DisplayRenderingPolicySfml
    >
    class Interpreter : private DisplayRenderingPolicy
    {
        public:
            Interpreter();
            ~Interpreter() = default;

            void LoadRom(std::string_view _rom);
            void StartRom(bool async = true);

            void Pause();
            void Continue();
            void Step();
            bool IsRunning() const;

            void SetCpuFrequency(timers::Frequency _new_frequency);
            void SetTimersFrequency(timers::Frequency _new_frequency);

        private:
            void InitializeRam();
            void ProcessInstruction(const opcodes::OpBytes& _op_bytes);

            void CpuCycle();
            void InstructionCycle();
            void TickTimers();

            void ExecuteInstruction_0NNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_00E0(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_00EE(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_1NNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_2NNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_3XNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_4XNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_5XY0(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_6XNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_7XNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY0(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY1(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY2(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY3(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY4(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY5(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY6(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XY7(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_8XYE(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_9XY0(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_ANNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_BNNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_CXNN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_DXYN(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_EX9E(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_EXA1(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX07(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX0A(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX15(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX18(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX1E(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX29(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX33(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX55(const opcodes::OpBytes& op_bytes); 
            void ExecuteInstruction_FX65(const opcodes::OpBytes& op_bytes); 

        private:
            memory::Ram     ram_{};
            memory::RamIter program_counter_{};

            io::display::PixelArray pixels_ {};
            io::Keypad              keypad_ {};
            io::Speaker             speaker_{};

            timers::Timer delay_timer_{};
            timers::Timer sound_timer_;

            timers::RateGuard cpu_cycle_guard_;
            timers::RateGuard timers_tick_guard_;

            registers::IRegister i_register_{};
            registers::DataRegisters data_registers_{};

            std::vector<memory::RamIter> stack_{};

            tasks::RecurrentTask cpu_task_;

            log::CoutLogger cout_logger_;

            const memory::RamIter program_memory_begin_   { ram_.begin() + memory::begin_program_ram };
            const memory::RamIter interpreter_memory_end_ { ram_.begin() + memory::interpreter_ram_size };

            friend class test::Interpreter;
            friend class QInterpreter;
    };
}

#include "InterpreterImpl.hpp"
#include "InterpreterOpcodesImpl.hpp"

#endif
