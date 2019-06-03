#include <chrono>
#include <thread>

#include "io/Keypad.hpp"

namespace chip8::io
{
    uint8_t Keypad::WaitForKey() const
    {
        while(true)
        {
            for(uint8_t hex = 0; hex < KeyMap::num_keys; hex++)
            {
                if(IsKeyPressed(hex)) { return hex; }
            }

            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(100ms); 
        }
    }

    bool Keypad::IsKeyPressed(uint8_t _hex) const
    {
        const auto key =  keymap_.GetKey(_hex);

        return IsKeyPressed(key);
    }

    bool Keypad::IsKeyPressed(sf::Keyboard::Key _key) const
    {
        return sf::Keyboard::isKeyPressed(_key);
    }

    void Keypad::SetKeyMapping(const KeyMap::KeyMapping& _new_key_mapping)
    {
        keymap_.SetMapping(_new_key_mapping);
    }
}
