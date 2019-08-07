#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Interpreter.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <string>

#include "details/opcodes.hpp"

namespace chip8::test
{

    class Interpreter : public chip8::Interpreter { 
        public: 
            /**
            * Test OpCode 0NNN 
            * Jump to a machine code routine at nnn. This instruction is only used on the old computers on which Chip-8
            * was originally implemented. It is ignored by modern interpreters. This will not be implemented.
            */
            void TestOpCode_0NNN() {
                try {
                    chip8::opcodes::OpBytes op{0x01, 0x23}; // NOLINT
                    ProcessInstruction(op);
                    FAIL() << "Expected 0x0NNN chip8::OpCodeException";
                }
                catch(chip8::OpCodeException const & err) {
                    EXPECT_THAT(err.what(), ::testing::MatchesRegex("0x0...: Instruction not implemented. ROM not supported."));
                }
                catch(...) {
                    FAIL() << "Expected 0x0NNN chip8::OpCodeException";
                }
            }

            /**
            * Test OpCode 00E0 
            * Clear the pixel frame buffer.
            */
            void TestOpCode_00E0() {
                pixels_.WriteByteAt(0,0, 0xFF); // NOLINT

                chip8::opcodes::OpBytes op{0x00, 0xE0}; // NOLINT
                ProcessInstruction(op);

                for (const auto& pixel : pixels_)
                {
                    EXPECT_TRUE(pixel == 0);
                }
            }

            /**
            * Test OpCode 00EE
            * Return from a subrutine.
            */
            void TestOpCode_00EE() {
                // Set the program counter to 0x234 and jump to subrutine starting at 0x111
                // The return from subrutine

                program_counter_ = ram_.begin() + 0x234; // NOLINT

                chip8::opcodes::OpBytes op_2NNN{0x21, 0x11}; // NOLINT
                ProcessInstruction(op_2NNN);

                EXPECT_EQ(stack_.back() - ram_.begin(), 0x234); // NOLINT
                EXPECT_EQ(program_counter_ - ram_.begin(), 0x111); // NOLINT

                auto stack_size_before_returning = stack_.size();

                chip8::opcodes::OpBytes op_00EE{0x00, 0xEE}; // NOLINT
                ProcessInstruction(op_00EE);

                auto stack_size_after_returning = stack_.size();

                EXPECT_EQ(stack_size_before_returning - stack_size_after_returning, 1); // NOLINT
                EXPECT_EQ(program_counter_ - ram_.begin(), 0x234); // NOLINT

            }

            /**
            * Test OpCode 1NNN
            * Jump to address NNN.
            */
            void TestOpCode_1NNN() {
                chip8::opcodes::OpBytes op{0x11, 0x11}; // NOLINT
                ProcessInstruction(op);
                EXPECT_EQ(program_counter_ - ram_.begin(), 0x111); // NOLINT
            }

            /**
            * Test OpCode 2NNN 
            * Execute subroutine starting at address NNN
            */
            void TestOpCode_2NNN() {
                // Set the program counter to 0x234 and jump to subrutine starting at 0x111

                program_counter_ = ram_.begin() + 0x234; // NOLINT

                chip8::opcodes::OpBytes op{0x21, 0x11}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(stack_.back() - ram_.begin(), 0x234); // NOLINT
                EXPECT_EQ(program_counter_ - ram_.begin(), 0x111); // NOLINT

            }

            /**
            * Test OpCode 3XNN 
            * Skip the following instruction if the value of register VX equals NN
            */
            void TestOpCode_3XNN()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                chip8::opcodes::OpBytes op {0x31, 11}; // NOLINT
                ProcessInstruction(op);

                //The program counter should have jumped the next instruction
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT

                op = {0x30, 11}; // NOLINT
                ProcessInstruction(op);

                //The program counter shouldn't jump with the second instrution
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT
            }

            /**
            * Test OpCode 4XNN 
            * Skip the following instruction if the value of register VX is not equal to NN
            */
            void TestOpCode_4XNN()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                chip8::opcodes::OpBytes op {0x41, 11}; // NOLINT
                ProcessInstruction(op);

                //The program counter should not have jumped the next instruction
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 0); // NOLINT

                op = {0x40, 11}; // NOLINT
                ProcessInstruction(op);

                //The program counter should have jumped with the second instrution
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT
            }

            /**
            * Test OpCode 5XY0 
            * Skip the following instruction if the value of register VX is equal to VY
            */
            void TestOpCode_5XY0()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(11);
                data_registers_[2].Set(10);

                chip8::opcodes::OpBytes op {0x50, 0x10}; // NOLINT
                ProcessInstruction(op);

                //The program counter should not have jumped the next instruction
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 0); // NOLINT

                op = {0x50, 0x20}; // NOLINT
                ProcessInstruction(op);

                //The program counter should have jumped with the second instrution
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT
            }

            /**
            * Test OpCode 6XNN 
            * Store number NN in register VX
            */
            void TestOpCode_6XNN()
            {
                data_registers_[3].Set(10);

                EXPECT_EQ(data_registers_[3].Get(), 10); // NOLINT

                chip8::opcodes::OpBytes op {0x63, 90}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[3].Get(), 90); // NOLINT
            }

            /**
            * Test OpCode 7XNN 
            * Store number NN in register VX
            */
            void TestOpCode_7XNN()
            {
                data_registers_[3].Set(10);

                EXPECT_EQ(data_registers_[3].Get(), 10); // NOLINT

                chip8::opcodes::OpBytes op {0x73, 90}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[3].Get(), 100); // NOLINT
            }

            /**
            * Test OpCode 8XY0 
            * Store the value of VY in VX
            */
            void TestOpCode_8XY0()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x10}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), data_registers_[1].Get()); // NOLINT
            }

            /**
            * Test OpCode 8XY1 
            * Set VX to VX OR VY
            */
            void TestOpCode_8XY1()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x11}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), 10 | 11); // NOLINT
            }

            /**
            * Test OpCode 8XY2 
            * Set VX to VX AND VY
            */
            void TestOpCode_8XY2()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x12}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), 10 & 11); // NOLINT
            }

            /**
            * Test OpCode 8XY3 
            * Set VX to VX XOR VY
            */
            void TestOpCode_8XY3()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x13}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), 10 ^ 11); // NOLINT
            }

            /**
            * Test OpCode 8XY4 
            * Add the value of VY to VX with carry
            */
            void TestOpCode_8XY4()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x14}; // NOLINT
                ProcessInstruction(op);

                //No carry
                EXPECT_EQ(data_registers_[0xF].Get(), 0); // NOLINT

                data_registers_[0].Set(255);
                data_registers_[1].Set(1);

                EXPECT_EQ(data_registers_[0].Get(), 255); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 1); // NOLINT

                ProcessInstruction(op);

                //Carry should be detected
                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT
            }

            /**
            * Test OpCode 8XY5 
            * Subtract the value of VY to VX with carry
            */
            void TestOpCode_8XY5()
            {
                data_registers_[0].Set(10);
                data_registers_[1].Set(9);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 9); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x15}; // NOLINT
                ProcessInstruction(op);

                //No carry
                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT
                EXPECT_EQ(data_registers_[0].Get(), uint8_t(10 - 9)); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 9); // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(11);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT

                ProcessInstruction(op);

                //Carry should be detected
                EXPECT_EQ(data_registers_[0xF].Get(), 0); // NOLINT
                EXPECT_EQ(data_registers_[0].Get(), uint8_t(10 - 11)); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 11); // NOLINT
            }

            /**
            * Test OpCode 8XY6 
            * Shift register VX to the right. VY is ignored.
            * Set register VF to the least significant bit prior to the shift
            */
            void TestOpCode_8XY6()
            {
                data_registers_[0].Set(0b11);
                data_registers_[0xF].Set(0);

                EXPECT_EQ(data_registers_[0].Get(), 0b11); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 0x0); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x16}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), 0x1); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 0x1); // NOLINT
            }

            /**
            * Test OpCode 8XY7 
            * Set register VX to the value of VY minus VX. Set VF to carry
            */
            void TestOpCode_8XY7()
            {
                data_registers_[0].Set(9);
                data_registers_[1].Set(10);
                data_registers_[0xF].Set(0);

                EXPECT_EQ(data_registers_[0].Get(), 9); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 0); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x17}; // NOLINT
                ProcessInstruction(op);

                //No borrow
                EXPECT_EQ(data_registers_[0].Get(), 1); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(9);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 9); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT

                ProcessInstruction(op);

                //Borrow should be detected
                EXPECT_EQ(data_registers_[0].Get(), 255); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 9); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 0); // NOLINT
            }

            /**
            * OpCode 8XYE 
            * Shift register VX to the left. VY is ignored.
            * Set register VF to the most significant bit prior to the shift.
            */
            void TestOpCode_8XYE()
            {
                data_registers_[0].Set(0b10000001);
                data_registers_[0xF].Set(0);

                EXPECT_EQ(data_registers_[0].Get(), 0b10000001); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 0x0); // NOLINT

                chip8::opcodes::OpBytes op {0x80, 0x1E}; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(data_registers_[0].Get(), 0b00000010); // NOLINT
                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT
            }

            /**
            * Test OpCode 9XY0 
            * Skip the following instruction if the value of register VX is not equal to VY
            */
            void TestOpCode_9XY0()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[0].Set(10);
                data_registers_[1].Set(11);
                data_registers_[2].Set(10);

                chip8::opcodes::OpBytes op {0x90, 0x10}; // NOLINT
                ProcessInstruction(op);

                //The program counter should have jumped the next instruction
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT

                op = {0x90, 0x20}; // NOLINT
                ProcessInstruction(op);

                //The program counter should not have jumped with the second instrution
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT
            }

            /**
            * OpCode ANNN 
            * Store memory address NNN in register I
            */
            void TestOpCode_ANNN() {
                chip8::opcodes::OpBytes op_A123{0xA1, 0x23}; // NOLINT
                ProcessInstruction(op_A123);
                EXPECT_EQ(i_register_.Get(), 0x123);

                chip8::opcodes::OpBytes op_A234{0xA2, 0x34}; // NOLINT
                ProcessInstruction(op_A234);
                EXPECT_EQ(i_register_.Get(), 0x234);

            }

            /**
            * Test OpCode BNNN
            * Jump to address NNN + V0.
            */
            void TestOpCode_BNNN()
            {
                program_counter_ = ram_.begin(); // NOLINT

                data_registers_[0].Set(10);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT

                opcodes::OpBytes op { 0xB1, 0x11 }; // NOLINT
                ProcessInstruction(op);

                EXPECT_EQ(std::distance(ram_.begin(), program_counter_), 0x111 + 10); // NOLINT
            }

            /**
            * Test OpCode CXNN
            * Set VX to a random number with a mask of NN
            */
            void TestOpCode_CXNN()
            {
                opcodes::OpBytes op { 0xC0, 0x0A }; // NOLINT

                for(size_t i = 0; i < 100; i++)
                {
                    ProcessInstruction(op);
                    EXPECT_LE(data_registers_[0].Get(), 0x0A); // NOLINT
                    EXPECT_GE(data_registers_[0].Get(), 0x00); // NOLINT
                }
            }

            /**
            * Test OpCode DXYN 
            * Draw a sprite at position VX, VY with N bytes of sprite data starting at the address 
            * stored in I. Set VF to 1 if any set pixels are changed to unset, and 0 otherwise.
            */
            void TestOpCode_DXYN() {
                using namespace std::literals::chrono_literals;

                chip8::opcodes::OpBytes op_00E0{0x00, 0xE0}; // NOLINT
                ProcessInstruction(op_00E0);

                i_register_.Set(5*0); // NOLINT

                chip8::opcodes::OpBytes op_D005{0xD0, 0x05}; // NOLINT
                ProcessInstruction(op_D005);

                EXPECT_EQ(data_registers_[0xF].Get(), 0); // NOLINT

                std::this_thread::sleep_for(0.2s);

                i_register_.Set(5*1); // NOLINT
                ProcessInstruction(op_D005);

                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT

                std::this_thread::sleep_for(0.2s);

                i_register_.Set(5*2); // NOLINT
                ProcessInstruction(op_D005);

                EXPECT_EQ(data_registers_[0xF].Get(), 1); // NOLINT

                std::this_thread::sleep_for(0.2s);

                i_register_.Set(5*3); // NOLINT
                ProcessInstruction(op_D005);

                std::this_thread::sleep_for(0.2s);

            }

            /**
            * Test OpCode EX9E 
            * Skip the following instruction if the key corresponding to the hex value currently
            * stored in register VX is pressed
            */
            void TestOpCode_EX9E()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[1].Set(0x0);
                EXPECT_EQ(data_registers_[1].Get(), 0x0); // NOLINT

                chip8::opcodes::OpBytes op {0xE1, 0x9E}; // NOLINT
                ProcessInstruction(op);

                //The program counter should not have jumped the next instruction
                //(the key was not pressed)
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 0); // NOLINT
            }

            /**
            * Test OpCode EXA1 
            * Skip the following instruction if the key corresponding to the hex value currently
            * stored in register VX is not being pressed
            */
            void TestOpCode_EXA1()
            {
                program_counter_ = program_memory_begin_; // NOLINT

                data_registers_[1].Set(0x0);
                EXPECT_EQ(data_registers_[1].Get(), 0x0); // NOLINT

                chip8::opcodes::OpBytes op {0xE1, 0xA1}; // NOLINT
                ProcessInstruction(op);

                //The program counter should have jumped the next instruction
                //(the key was not pressed)
                EXPECT_EQ(std::distance(program_memory_begin_, program_counter_), 2); // NOLINT
            }

            /*
            * Test OpCode FX07 
            * Store the curent value of the delay timer in register VX
            */
            void TestOpCode_FX07()
            {
                opcodes::OpBytes op { 0xF0, 0x07 }; // NOLINT

                delay_timer_.SetValue(10);

                while(delay_timer_.GetValue() != 0)
                {
                    ProcessInstruction(op);
                    EXPECT_EQ(data_registers_[0].Get(), delay_timer_.GetValue()); // NOLINT
                    delay_timer_.Tick();
                }
            }

            /**
            * Test OpCode FX0A 
            * Wait for a keypress and store the result in register VX
            */
            void TestOpCode_FX0A()
            {
                //TODO: implement tests for this (WaitForKey blocks)
            }

            /**
            * Test OpCode FX15 
            * Set the delay timer to the value of register VX
            */
            void TestOpCode_FX15()
            {
                opcodes::OpBytes op { 0xF0, 0x15 }; // NOLINT

                data_registers_[0].Set(10);
                delay_timer_.SetValue(0);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(delay_timer_.GetValue(), 0); // NOLINT

                ProcessInstruction(op);
                EXPECT_EQ(data_registers_[0].Get(), delay_timer_.GetValue()); // NOLINT
            }

            /**
            * Test OpCode FX18 
            * Set the sound timer to the value of register VX
            */
            void TestOpCode_FX18()
            {
                opcodes::OpBytes op { 0xF0, 0x18 }; // NOLINT

                data_registers_[0].Set(10);
                sound_timer_.SetValue(0);

                EXPECT_EQ(data_registers_[0].Get(), 10); // NOLINT
                EXPECT_EQ(sound_timer_.GetValue(), 0); // NOLINT

                ProcessInstruction(op);
                EXPECT_EQ(data_registers_[0].Get(), sound_timer_.GetValue()); // NOLINT
            }

            /**
            * Test OpCode FX1E 
            * Add the value stored in register VX to register I
            */
            void TestOpCode_FX1E()
            {
                opcodes::OpBytes op { 0xF1, 0x1E }; // NOLINT

                data_registers_[1].Set(10);
                i_register_.Set(15);

                EXPECT_EQ(data_registers_[1].Get(), 10); // NOLINT
                EXPECT_EQ(i_register_.Get(), 15); // NOLINT

                for(size_t i = 0; i < 10; i++)
                {
                    ProcessInstruction(op);
                    EXPECT_EQ(i_register_.Get(), 15 + data_registers_[1].Get() * (i + 1)); // NOLINT
                }
            }

            /**
            * Test OpCode FX29
            * Set I to the memory address of the sprite data corresponding to the 
            * hexadecimal digit stored in register VX
            */
            void TestOpCode_FX29()
            {
                data_registers_[2].Set(0xA); // NOLINT
                opcodes::OpBytes op_F229 { 0xF2, 0x29 }; // NOLINT
                ProcessInstruction(op_F229);
                EXPECT_EQ(i_register_.Get(), 5*0xA); // NOLINT
            }

            /**
            * Test OpCode FX33
            * Store the binary-coded decimal equivalent of the value stored 
            * in register VX at addresses I, I+1, and I+2
            */
            void TestOpCode_FX33()
            {
                data_registers_[2].Set(123); // NOLINT

                opcodes::OpBytes op_F233 { 0xF2, 0x33 }; // NOLINT
                ProcessInstruction(op_F233);

                EXPECT_EQ(ram_.at(i_register_.Get()+0), 1); // NOLINT
                EXPECT_EQ(ram_.at(i_register_.Get()+1), 2); // NOLINT
                EXPECT_EQ(ram_.at(i_register_.Get()+2), 3); // NOLINT
            }

            /**
            * Test OpCode FX55
            * Store the values of registers V0 to VX inclusive in memory starting at address I
            * I is set to I + X + 1 after operation
            */
            void TestOpCode_FX55()
            {
                data_registers_[0].Set(0); // NOLINT
                data_registers_[1].Set(1); // NOLINT
                data_registers_[2].Set(2); // NOLINT
                data_registers_[3].Set(3); // NOLINT

                const uint16_t i_0 = 300;
                i_register_.Set(i_0);

                opcodes::OpBytes op_F355 { 0xF3, 0x55 }; // NOLINT
                ProcessInstruction(op_F355);

                EXPECT_EQ(ram_.at(i_0+0), 0); // NOLINT
                EXPECT_EQ(ram_.at(i_0+1), 1); // NOLINT
                EXPECT_EQ(ram_.at(i_0+2), 2); // NOLINT
                EXPECT_EQ(ram_.at(i_0+3), 3); // NOLINT

                EXPECT_EQ(i_register_.Get(), i_0 + 3 + 1); // NOLINT
            }

            /**
            * Test OpCode FX65
            * Fill registers V0 to VX inclusive with the values stored in memory 
            * starting at address I. I is set to I + X + 1 after operation
            */
            void TestOpCode_FX65()
            {
                const uint16_t i_0 = 300;

                ram_.at(i_0 + 0) = 5; // NOLINT
                ram_.at(i_0 + 1) = 6; // NOLINT
                ram_.at(i_0 + 2) = 7; // NOLINT
                ram_.at(i_0 + 3) = 8; // NOLINT

                i_register_.Set(i_0);

                opcodes::OpBytes op_F365 { 0xF3, 0x65 }; // NOLINT
                ProcessInstruction(op_F365);

                EXPECT_EQ(data_registers_[0].Get(), 5); // NOLINT
                EXPECT_EQ(data_registers_[1].Get(), 6); // NOLINT
                EXPECT_EQ(data_registers_[2].Get(), 7); // NOLINT
                EXPECT_EQ(data_registers_[3].Get(), 8); // NOLINT

                EXPECT_EQ(i_register_.Get(), i_0 + 3 + 1); // NOLINT
            }

    };

    TEST(Chip8TestSuite, OpCodes)
    {
        chip8::test::Interpreter interpreterTests{};
        
        interpreterTests.TestOpCode_0NNN();
        interpreterTests.TestOpCode_00E0();
        interpreterTests.TestOpCode_00EE();
        interpreterTests.TestOpCode_1NNN();
        interpreterTests.TestOpCode_2NNN();
        interpreterTests.TestOpCode_3XNN();
        interpreterTests.TestOpCode_4XNN();
        interpreterTests.TestOpCode_5XY0();
        interpreterTests.TestOpCode_6XNN();
        interpreterTests.TestOpCode_7XNN();
        interpreterTests.TestOpCode_8XY0();
        interpreterTests.TestOpCode_8XY1();
        interpreterTests.TestOpCode_8XY2();
        interpreterTests.TestOpCode_8XY3();
        interpreterTests.TestOpCode_8XY4();
        interpreterTests.TestOpCode_8XY5();
        interpreterTests.TestOpCode_8XY6();
        interpreterTests.TestOpCode_8XY7();
        interpreterTests.TestOpCode_8XYE();
        interpreterTests.TestOpCode_9XY0();
        interpreterTests.TestOpCode_ANNN();
        interpreterTests.TestOpCode_BNNN();
        interpreterTests.TestOpCode_CXNN();
        interpreterTests.TestOpCode_DXYN();
        interpreterTests.TestOpCode_EX9E();
        interpreterTests.TestOpCode_EXA1();
        interpreterTests.TestOpCode_FX07();
        interpreterTests.TestOpCode_FX0A();
        interpreterTests.TestOpCode_FX15();
        interpreterTests.TestOpCode_FX18();
        interpreterTests.TestOpCode_FX1E();
        interpreterTests.TestOpCode_FX29();
        interpreterTests.TestOpCode_FX33();
        interpreterTests.TestOpCode_FX55();
        interpreterTests.TestOpCode_FX65();
    }
}
