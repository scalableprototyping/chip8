#ifndef CHIP_8_KEYPAD_HPP
#define CHIP_8_KEYPAD_HPP

#include <SFML/Window/Keyboard.hpp>

#include "io/KeyMap.hpp"

namespace chip8::io
{
    class Keypad
    {
        public:
            //Any better way to expose this in this class?
            static constexpr uint8_t num_keys { KeyMap::num_keys };

        public:
            ~Keypad() = default;

            uint8_t WaitForKey() const;

            bool IsKeyPressed(uint8_t _key) const;
            bool IsKeyPressed(sf::Keyboard::Key _key) const;

            void SetKeyMapping(const KeyMap::KeyMapping& _new_key_mapping);

        private:
            KeyMap keymap_;
    };
}

#endif
