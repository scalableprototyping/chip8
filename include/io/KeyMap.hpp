#ifndef CHIP_8_KEYMAP_HPP
#define CHIP_8_KEYMAP_HPP

#include <array>
#include <stdint.h> // for uint8_t

#include <SFML/Window/Keyboard.hpp>

namespace chip8::io
{
    class KeyMap
    {
        public:
            static constexpr uint8_t num_keys { 16 };
            //I felt using an actual std::map for this was overkill
            using KeyMapping = std::array<sf::Keyboard::Key, num_keys>;

        public:
            KeyMap();
            ~KeyMap() = default;

            sf::Keyboard::Key GetKey(uint8_t _hex) const;
            void SetMapping(const KeyMapping& _new_key_mapping);

            const KeyMapping& GetMapping() const { return key_mapping_; }

        private:
            bool IsMappingValid(const KeyMapping& _key_mapping) const;

        private:
            //Default values
            KeyMapping key_mapping_
            {
                sf::Keyboard::Key::Q,
                sf::Keyboard::Key::W,
                sf::Keyboard::Key::E,
                sf::Keyboard::Key::R,
                sf::Keyboard::Key::T,
                sf::Keyboard::Key::Y,
                sf::Keyboard::Key::U,
                sf::Keyboard::Key::I,
                sf::Keyboard::Key::O,
                sf::Keyboard::Key::P,
                sf::Keyboard::Key::A,
                sf::Keyboard::Key::S,
                sf::Keyboard::Key::D,
                sf::Keyboard::Key::F,
                sf::Keyboard::Key::G,
                sf::Keyboard::Key::H,
            };
    };
}

#endif
