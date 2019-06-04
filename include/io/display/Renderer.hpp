#pragma once

#include "io/display/PixelArray.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <algorithm>

namespace chip8::io::display
{
    class Renderer
    {
        public:
            Renderer() = delete;
            explicit Renderer(PixelArray& pixels);
            void Update();

        private:
            const PixelArray& pixels_;

            void UpdatePixels();

            class PixelQuads : public sf::Drawable, public sf::Transformable
            {
                public:
                    PixelQuads() = delete;
                    explicit PixelQuads(const PixelArray& pixels);

                    void Update();

                    const int kTextureHeight_ = 32;
                    const int kTextureWidth_ = 32;

                private:
                    const PixelArray& pixels_;

                    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                    sf::VertexArray vertices_;
                    sf::Texture pixelsTexture_;
                    const std::string kTileSetTexturePath_{
                        std::string{ASSETS_PATH} + "tileset.png"
                    };
                    std::vector<sf::Vector2f> pixelOffTextureCoords;
                    std::vector<sf::Vector2f> pixelOnTextureCoords;
                    using pixelTextureCoords_t = std::vector<std::vector<sf::Vector2f>>;
                    pixelTextureCoords_t pixelTextureCoords; 
            };
            PixelQuads pixelQuads_;

            sf::RenderWindow window_{sf::VideoMode(800, 600), "Chip8 Display"};
    };
}
