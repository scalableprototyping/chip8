#ifndef CHIP_8_RENDERER_HPP
#define CHIP_8_RENDERER_HPP

#include <SFML/Graphics/Drawable.hpp>       // for Drawable
#include <SFML/Graphics/RenderStates.hpp>   // for RenderStates
#include <SFML/Graphics/RenderWindow.hpp>   // for RenderWindow
#include <SFML/Graphics/Texture.hpp>        // for Texture
#include <SFML/Graphics/Transformable.hpp>  // for Transformable
#include <SFML/Graphics/VertexArray.hpp>    // for VertexArray
#include <SFML/System/Vector2.hpp>          // for Vector2f
#include <SFML/Window/VideoMode.hpp>        // for VideoMode

#include <memory>
#include <string>
#include <vector>

namespace chip8::io::display { class PixelArray; }
namespace sf { class RenderTarget; }

namespace chip8::io::display
{
    class DisplayRenderingPolicySfml
    {
        protected:
            Renderer() = delete;
            explicit Renderer(PixelArray& pixels);
            void Begin();
            void Update();

        private:
            const PixelArray& pixels_;

            class PixelQuads : public sf::Drawable, public sf::Transformable
            {
                public:
                    PixelQuads() = delete;
                    explicit PixelQuads(const PixelArray& pixels);

                    void Update();

                    static constexpr int kTextureHeight_ = 32;
                    static constexpr int kTextureWidth_ = 32;

                private:
                    const PixelArray& pixels_;

                    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                    sf::VertexArray vertices_;
                    sf::Texture pixelsTexture_;
                    const std::string kTileSetTexturePath_{
                        "assets/tileset.png"
                    };
                    std::vector<sf::Vector2f> pixelOffTextureCoords;
                    std::vector<sf::Vector2f> pixelOnTextureCoords;
                    using pixelTextureCoords_t = std::vector<std::vector<sf::Vector2f>>;
                    pixelTextureCoords_t pixelTextureCoords; 
            };
            PixelQuads pixelQuads_;

            std::unique_ptr<sf::RenderWindow> window_;
    };
}

#endif
