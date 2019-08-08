#ifndef CHIP_8_STRCAT_HPP
#define CHIP_8_STRCAT_HPP

#include <string>
#include <type_traits>

namespace chip8::utils
{
    template <class LastStr>
    std::enable_if_t<std::is_constructible<std::string, LastStr>::value, std::string>
    strcat(const LastStr& _last)
    {
        return _last;
    }

    template <class LastStr>
    std::enable_if_t<std::is_same<std::string, decltype(std::to_string(std::declval<LastStr&>()))>::value, std::string>
    strcat(const LastStr& _last)
    {
        return std::to_string(_last);
    }

    //Specialization for chip8::toStr functions
    template <class LastStr>
    std::enable_if_t<std::is_same<std::string, decltype(toStr(std::declval<LastStr&>()))>::value, std::string>
    strcat(const LastStr& _last)
    {
        return toStr(_last);
    }

    template <class FirstStr, class... Others>
    std::string strcat(const FirstStr& _first, const Others&... _others)
    {
        return strcat(_first) + strcat(_others...);
    }
}

#endif
