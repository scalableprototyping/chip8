namespace chip8::details
{
    template<typename UnaryFunction>
    void forEachBitInByte(uint8_t byte, UnaryFunction&& f)
    {
        for(auto i=0; i<8; ++i)    
        {    
            auto bit = byte%2;    
            f(bit);
            byte /= 2;  
        }    
    }
}
