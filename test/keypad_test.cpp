#include <gtest/gtest.h>

#include "io/Keypad.hpp"

#include <memory>

namespace chip8::test
{
    TEST(Chip8TestSuite, KeyMap)
    {
        //This is defined as a smart ptr to test for exceptions in the constructor
        std::unique_ptr<io::KeyMap> key_map;
        ASSERT_NO_THROW(key_map = std::make_unique<io::KeyMap>());

        const auto& mapping = key_map->GetMapping();
        ASSERT_EQ(io::KeyMap::num_keys, mapping.size());

        //Valid mapping
        ASSERT_NO_THROW(key_map->SetMapping(mapping));

        //Invalid mappings
        io::KeyMap::KeyMapping empty_mapping {};
        ASSERT_THROW(key_map->SetMapping(empty_mapping), std::runtime_error);

        io::KeyMap::KeyMapping repeated_mapping = key_map->GetMapping();
        repeated_mapping.back() = repeated_mapping.front();
        ASSERT_THROW(key_map->SetMapping(repeated_mapping), std::runtime_error);

        //Valid queries
        for(uint8_t hex = 0x0; hex < io::KeyMap::num_keys; hex++)
        {
            ASSERT_NO_THROW(key_map->GetKey(hex));
        }

        //Invalid queries
        ASSERT_THROW(key_map->GetKey(0x10), std::runtime_error);
    }

    TEST(Chip8TestSuite, Keypad)
    {
        //How should the actual keypad be tested?
    }
}
