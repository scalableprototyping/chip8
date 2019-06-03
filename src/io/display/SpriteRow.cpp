#include "io/display/SpriteRow.hpp"

namespace chip8::io::display
{
    using BitValue_t = SpriteRow::BitValue_t;
    using Iterator_t = SpriteRow::Iterator_t;
    using ConstIterator_t = SpriteRow::ConstIterator_t;
    using ReverseIterator_t = SpriteRow::ReverseIterator_t;
    using ConstReverseIterator_t = SpriteRow::ConstReverseIterator_t;

    SpriteRow::SpriteRow(uint8_t byte)
    {
        for(auto i=0; i<8; ++i)    
        {    
            bits_[i] = byte%2;    
            byte /= 2;  
        }    
    }

    BitValue_t& SpriteRow::at(uint8_t index)
    {
        return bits_.at(index);
    }

    const BitValue_t& SpriteRow::at(uint8_t index) const
    {
        return bits_.at(index);
    }

    Iterator_t SpriteRow::iterator_at(uint8_t index)
    {
        throwIfOutOfRange(index);
        return bits_.begin() + index;
    }

    ConstIterator_t SpriteRow::iterator_at(uint8_t index) const
    {
        throwIfOutOfRange(index);
        return bits_.begin() + index;
    }

    Iterator_t SpriteRow::begin() 
    { 
        return bits_.begin(); 
    }

    Iterator_t SpriteRow::end() 
    { 
        return bits_.end(); 
    }

    ConstIterator_t SpriteRow::begin() const 
    { 
        return bits_.begin(); 
    }

    ConstIterator_t SpriteRow::end() const 
    { 
        return bits_.end(); 
    }

    ReverseIterator_t SpriteRow::rbegin() 
    { 
        return bits_.rbegin(); 
    }

    ReverseIterator_t SpriteRow::rend() 
    { 
        return bits_.rend(); 
    }

    ConstReverseIterator_t SpriteRow::rbegin() const 
    { 
        return bits_.rbegin(); 
    }

    ConstReverseIterator_t SpriteRow::rend() const 
    { 
        return bits_.rend(); 
    }

    ConstIterator_t SpriteRow::cbegin() const 
    { 
        return bits_.cbegin(); 
    }

    ConstIterator_t SpriteRow::cend() const 
    { 
        return bits_.cend(); 
    }

    ConstReverseIterator_t SpriteRow::crbegin() const 
    { 
        return bits_.crbegin(); 
    }

    ConstReverseIterator_t SpriteRow::crend() const 
    { 
        return bits_.crend(); 
    }

    void SpriteRow::throwIfOutOfRange(uint8_t index) const
    {
        if (index >= kWidth_)
        {
            throw std::out_of_range ("Trying to access SpriteRow index out of range.");
        }
    }
}
