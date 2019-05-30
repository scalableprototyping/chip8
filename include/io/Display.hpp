#include <cstdint>
#include <stdexcept>

#include <SFML/Graphics.hpp>

namespace chip8::io
{
    class DisplayPixels
    {
        public:
            using PixelValue_t = bool;

            static const int kWidth_ = 64;
            static const int kHeight_ = 32;

            DisplayPixels();
            void Clear();

            class PixelColumn 
            {
                public:
                    friend DisplayPixels;
                    PixelValue_t& operator[](std::size_t row)
                    {
                        if (col_ >= parent_.kWidth_ || row >= parent_.kHeight_)
                        {
                            throw std::out_of_range ("Trying to access display pixel index out of range.");
                        }
                        return parent_.pixels_[col_][row];
                    }
                private:
                    PixelColumn(DisplayPixels &parent, std::size_t col) : 
                        parent_(parent), col_(col) {}
                    DisplayPixels& parent_;
                    std::size_t col_;
            };

            PixelColumn operator[](std::size_t col)
            {
                return PixelColumn(*this, col);
            }

        private:
            using PixelsColum_t = std::array<PixelValue_t, kHeight_>;
            using Pixels_t = std::array<PixelsColum_t, kWidth_>;
            Pixels_t pixels_;
    };

    class DisplayRenderer
    {
        public:
            DisplayRenderer() = delete;
            explicit DisplayRenderer(DisplayPixels& displayPixels);
            void Update();

        private:
            // TODO:
            // How can I make this const?? I don't want the renderer to be able to write here
            DisplayPixels& displayPixels_;

            class TileMap : public sf::Drawable, public sf::Transformable
        {
            public:
                TileMap() = delete;
                TileMap(DisplayPixels& displayPixels);

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
                DisplayPixels& displayPixels_;
        };
            TileMap tileMap_;

            sf::RenderWindow window_{sf::VideoMode(800, 600), "Chip8 Display"};
    };
}
