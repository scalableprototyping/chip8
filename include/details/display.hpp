#ifndef CHIP_8_DETAILS_DISPLAY_HPP
#define CHIP_8_DETAILS_DISPLAY_HPP

namespace chip8::details
{
    template<typename BinaryFunction>
    void forEachBitInByteLittleEndian(uint8_t byte, BinaryFunction&& f)
    {
        for(auto bit_index_little_endian=0; bit_index_little_endian<8; ++bit_index_little_endian)    
        {    
            auto bit = byte%2;    
            f(bit_index_little_endian, bit);
            byte /= 2;  
        }    
    }
}

#endif
