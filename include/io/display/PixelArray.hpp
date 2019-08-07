#ifndef CHIP_8_PIXELARRAY_HPP
#define CHIP_8_PIXELARRAY_HPP

#include <array>
#include <cstdint>

namespace chip8::io::display
{
    class PixelArray
    {
        public:
            using PixelValue_t = uint8_t;
            static constexpr uint8_t kWidth_ = 64;
            static constexpr uint8_t kHeight_ = 32;
            using Array_t = std::array<PixelValue_t, kHeight_*kWidth_>;
            using Iterator_t = Array_t::iterator;
            using ConstIterator_t = Array_t::const_iterator;
            using ReverseIterator_t = Array_t::reverse_iterator;
            using ConstReverseIterator_t = Array_t::const_reverse_iterator;

            PixelArray();
            PixelArray (const PixelArray&) = delete;
            PixelArray& operator= (const PixelArray&) = delete;

            void Clear();
            using CollisionFlag = bool;
            CollisionFlag WriteByteAt(uint8_t _col, uint8_t _row, uint8_t _byte);

            PixelValue_t& at(uint8_t _col, uint8_t _row);
            const PixelValue_t& at(uint8_t _col, uint8_t _row) const;

            Iterator_t iterator_at(uint8_t _col, uint8_t _row);
            ConstIterator_t iterator_at(uint8_t _col, uint8_t _row) const;

            Iterator_t begin();
            Iterator_t end();

            ConstIterator_t begin() const;
            ConstIterator_t end() const;

            ReverseIterator_t rbegin();
            ReverseIterator_t rend();

            ConstReverseIterator_t rbegin() const;
            ConstReverseIterator_t rend() const;

            ConstIterator_t cbegin() const;
            ConstIterator_t cend() const;

            ConstReverseIterator_t crbegin() const;
            ConstReverseIterator_t crend() const;

        private:
            Array_t pixels_{};
            void throwIfOutOfRange(uint8_t col, uint8_t row) const;
    };
}

#endif
