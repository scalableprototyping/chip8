#include "io/display/PixelArray.hpp"

namespace chip8::io::display
{
    using PixelValue_t = PixelArray::PixelValue_t;
    using Iterator_t = PixelArray::Iterator_t;
    using ConstIterator_t = PixelArray::ConstIterator_t;
    using ReverseIterator_t = PixelArray::ReverseIterator_t;
    using ConstReverseIterator_t = PixelArray::ConstReverseIterator_t;

    PixelArray::PixelArray() 
    { 
        Clear(); 
    }

    void PixelArray::Clear() 
    { 
        pixels_.fill(0); 
    }

    PixelValue_t& PixelArray::at(uint8_t col, uint8_t row)
    {
        throwIfOutOfRange(col, row);
        return pixels_.at(row*kWidth_ + col);
    }

    const PixelValue_t& PixelArray::at(uint8_t col, uint8_t row) const
    {
        throwIfOutOfRange(col, row);
        return pixels_.at(row*kWidth_ + col);
    }

    Iterator_t PixelArray::iterator_at(uint8_t col, uint8_t row)
    {
        throwIfOutOfRange(col, row);
        return pixels_.begin() + (row*kWidth_ + col);
    }

    ConstIterator_t PixelArray::iterator_at(uint8_t col, uint8_t row) const
    {
        throwIfOutOfRange(col, row);
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

    ConstIterator_t PixelArray::begin() const 
    { 
        return pixels_.begin(); 
    }

    ConstIterator_t PixelArray::end() const 
    { 
        return pixels_.end(); 
    }

    ReverseIterator_t PixelArray::rbegin() 
    { 
        return pixels_.rbegin(); 
    }

    ReverseIterator_t PixelArray::rend() 
    { 
        return pixels_.rend(); 
    }

    ConstReverseIterator_t PixelArray::rbegin() const 
    { 
        return pixels_.rbegin(); 
    }

    ConstReverseIterator_t PixelArray::rend() const 
    { 
        return pixels_.rend(); 
    }

    ConstIterator_t PixelArray::cbegin() const 
    { 
        return pixels_.cbegin(); 
    }

    ConstIterator_t PixelArray::cend() const 
    { 
        return pixels_.cend(); 
    }

    ConstReverseIterator_t PixelArray::crbegin() const 
    { 
        return pixels_.crbegin(); 
    }

    ConstReverseIterator_t PixelArray::crend() const 
    { 
        return pixels_.crend(); 
    }

    void PixelArray::throwIfOutOfRange(uint8_t col, uint8_t row) const
    {
        if (col >= kWidth_)
        {
            throw std::out_of_range ("Trying to access column index out of range.");
        }
        if (row >= kHeight_)
        {
            throw std::out_of_range ("Trying to access row index out of range.");
        }
    }
}
