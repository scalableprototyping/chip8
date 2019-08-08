#pragma once
#ifndef CHIP_8_EXCEPTIONS_HPP
#define CHIP_8_EXCEPTIONS_HPP

#include <string>
#include <stdexcept>
#include <string_view>

#include "details/opcodes.hpp"
#include "utils/strcat.hpp"

namespace chip8
{

class Chip8Exception : public std::exception
{
  public:

    Chip8Exception(std::string_view _message):  message_(_message)
    {}

    template <class... Strings>
    Chip8Exception(const Strings&... _strings) : message_(utils::strcat(_strings...))
    {}

    const char* what() const noexcept
    {
        return message_.c_str();
    }

  private:
    std::string message_;
};

class OpCodeException : public Chip8Exception
{
  public:
    template <class... Strings>
    OpCodeException(const opcodes::OpBytes& _op_byte, const Strings&... _strings)
        : Chip8Exception(utils::strcat(_op_byte, ": ", _strings...))
    {}
};

}

#endif
