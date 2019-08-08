#pragma once
#ifndef CHIP_8_COUT_LOGGER_HPP
#define CHIP_8_COUT_LOGGER_HPP

#include <iostream>

#include "loggers/AbstractLogger.hpp"

namespace chip8::log
{
    class CoutLogger final : public AbstractLogger
    {
        public:
            ~CoutLogger() = default;

        private:
            virtual void LogInternal(std::string_view _message) override
            {
                std::cout << _message << "\n";
            };
    };
}

#endif
