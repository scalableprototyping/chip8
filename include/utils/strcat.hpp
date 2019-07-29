#ifndef CHIP_8_STRCAT_HPP
#define CHIP_8_STRCAT_HPP

#include <string_view>

namespace chip8::utils
{
    template <class LastStr>
    std::string strcat(const LastStr& _last)
    {
        return _last;
    }

    template <class FirstStr, class... Others>
    std::string strcat(const FirstStr& _first, const Others&... _others)
    {
        return _first + strcat(_others...);
    }
}

#endif
