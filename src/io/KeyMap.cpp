#include "io/KeyMap.hpp"

#include <set>        // for set
#include <stdexcept>  // for runtime_error, out_of_range
#include <string>     // for operator+, to_string

namespace chip8::io
{
    KeyMap::KeyMap()
    {
        //Should this be an assert instead
        if(!IsMappingValid(key_mapping_))
        {
            throw std::runtime_error { "KeyMap: invalid default key mapping" };
        }
    }

    sf::Keyboard::Key KeyMap::GetKey(uint8_t _hex) const
    {
        try
        {
            return key_mapping_.at(_hex);
        }
        catch(const std::out_of_range&)
        {
            throw std::runtime_error { "KeyMap: invalid hex key code " + std::to_string(_hex) };
        }
    }

    void KeyMap::SetMapping(const KeyMapping& _new_key_mapping)
    {
        if(!IsMappingValid(_new_key_mapping))
        {
            throw std::runtime_error { "KeyMap: trying to set invalid key mapping" };
        }

        key_mapping_ = _new_key_mapping;
    }

    //Private
    bool KeyMap::IsMappingValid(const KeyMapping& _key_mapping) const
    {
        //Check if all the keys are unique
        std::set<KeyMapping::value_type> unique_keys (_key_mapping.cbegin(), _key_mapping.cend());

        return unique_keys.size() == num_keys;
    }
}
