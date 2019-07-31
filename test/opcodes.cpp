#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Interpreter.hpp"

#include <iostream>
#include <string>

#include "details/opcodes.hpp"

namespace chip8::test
{

    class Interpreter : public chip8::Interpreter { 
        public: 
            void TestOpCode_0NNN() {
                try {
                    chip8::opcodes::OpBytes op{0x01, 0x23}; // NOLINT
                    processInstruction(op);
                    FAIL() << "Expected chip8::OpCodeException";
                }
                catch(chip8::OpCodeException const & err) {
                    EXPECT_THAT(err.what(), ::testing::HasSubstr("Instruction not implemented. ROM not supported."));
                }
                catch(...) {
                    FAIL() << "Expected chip8::OpCodeException";
                }
            }
    };

    TEST(Chip8TestSuite, OpCodes)
    {
        chip8::test::Interpreter interpreterTests{};
        
        interpreterTests.TestOpCode_0NNN();
        //interpreterTests.TestOpCode_00E0();
    }
}
