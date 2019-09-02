
#ifndef CHIP_8_DISPLAY_RENDERING_POLICY_DO_NOTHING_HPP
#define CHIP_8_DISPLAY_RENDERING_POLICY_DO_NOTHING_HPP

namespace chip8::io::display { class PixelArray; }

namespace chip8::io::display
{
    class DisplayRenderingPolicyDoNothing
    {
        protected:
            DisplayRenderingPolicyDoNothing() = delete;
            explicit DisplayRenderingPolicyDoNothing(PixelArray&) {};
            void Begin() {};
            void Update() {};
    };
}

#endif
