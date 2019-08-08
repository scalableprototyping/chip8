#pragma once
#ifndef CHIP_8_ABSTRACT_LOGGER_HPP
#define CHIP_8_ABSTRACT_LOGGER_HPP

#include <string_view>

#include "utils/strcat.hpp"

namespace chip8::log
{
    //TODO: add timestamps?
    class AbstractLogger
    {
        public:
            virtual ~AbstractLogger() = default;

            template <class... Strings>
            void Log(const Strings&... _strings)
            {
                LogInternal(utils::strcat(_strings...));
            }

        protected:
            virtual void LogInternal(std::string_view _message) = 0;
    };
}

#endif
