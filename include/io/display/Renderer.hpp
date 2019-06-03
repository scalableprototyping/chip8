#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace chip8::io::display
{
    class PixelArray;

    class Renderer
    {
        public:
            Renderer() = delete;
            explicit Renderer(PixelArray& pixels);
            void Update();

        private:
            // TODO:
            // How can I make this const?? I don't want the renderer to be able to write here
            PixelArray& pixels_;

            class TileMap : public sf::Drawable, public sf::Transformable
            {
                public:
                    TileMap() = delete;
                    TileMap(PixelArray& pixels);

                    void Update();
                    const std::string kTileSetTexturePath_{"../assets/tileset.png"};
                    const int kTextureHeight_ = 32;
                    const int kTextureWidth_ = 32;
                private:
                    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                    sf::VertexArray vertices_;
                    sf::Texture tileSetTexture_;
                    // TODO:
                    // How can I make this const?? I don't want tileMap to be able to write here
                    PixelArray& pixels_;
            };
            TileMap tileMap_;

            sf::RenderWindow window_{sf::VideoMode(800, 600), "Chip8 Display"};
    };
}
