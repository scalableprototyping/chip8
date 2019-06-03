#pragma once

#include <array>
#include <cstdint>

namespace chip8::io::display
{
    class SpriteRow
    {
        public:
            using BitValue_t = bool;
            static const uint8_t kWidth_ = 8;
            using Array_t = std::array<BitValue_t, kWidth_>;
            using Iterator_t = Array_t::iterator;
            using ConstIterator_t = Array_t::const_iterator;
            using ReverseIterator_t = Array_t::reverse_iterator;
            using ConstReverseIterator_t = Array_t::const_reverse_iterator;

            SpriteRow(uint8_t byte);

            BitValue_t& at(uint8_t index);
            const BitValue_t& at(uint8_t index) const;

            Iterator_t iterator_at(uint8_t index);
            ConstIterator_t iterator_at(uint8_t index) const;

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
            Array_t bits_;
            void throwIfOutOfRange(uint8_t index) const;
    };
}
