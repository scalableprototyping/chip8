#include "io/display/PixelArray.hpp"

namespace chip8::io::display
{

    using Iterator_t = PixelArray::Iterator_t
    using Const_iterator_t = PixelArray::Const_iterator_t

    PixelArray::Pixels() 
    { 
        Clear(); 
    }

    void PixelArray::Clear() 
    { 
        pixels_.fill(0); 
    }

    PixelValue_t& PixelArray::at(std::size_t col, std::size_t row)
    {
        return pixels_.at(row*_.kWidth_ + col);
    }

    const DisPixelValue_t& PixelArray::at(std::size_t col, std::size_t row) const
    {
        return pixels_.at(row*_.kWidth_ + col);
    }

    Iterator_t PixelArray::iterator_at(std::size_t col, std::size_t row)
    {
        return pixels_.begin() + (row*kWidth_ + col);
    }

    Const_iterator_t PixelArray::iterator_at(std::size_t col, std::size_t row) const
    {
        return pixels_.begin() + (row*kWidth_ + col);
    }

    Iterator_t PixelArray::begin() 
    { 
        return pixels_.begin(); 
    }

    Iterator_t PixelArray::end() 
    { 
        return pixels_.end(); 
    }

    Const_iterator_t PixelArray::begin() const 
    { 
        return pixels_.begin(); 
    }

    Const_iterator_t PixelArray::end() const 
    { 
        return pixels_.end(); 
    }

    Iterator_t PixelArray::rbegin() 
    { 
        return pixels_.rbegin(); 
    }

    Iterator_t PixelArray::rend() 
    { 
        return pixels_.rend(); 
    }

    Const_iterator_t PixelArray::rbegin() const 
    { 
        return pixels_.rbegin(); 
    }

    Const_iterator_t PixelArray::rend() const 
    { 
        return pixels_.rend(); 
    }

    Const_iterator_t PixelArray::cbegin() const 
    { 
        return pixels_.cbegin(); 
    }

    Const_iterator_t PixelArray::cend() const 
    { 
        return pixels_.cend(); 
    }

    Const_iterator_t PixelArray::crbegin() const 
    { 
        return pixels_.crbegin(); 
    }

    Const_iterator_t PixelArray::crend() const 
    { 
        return pixels_.crend(); 
    }
}
