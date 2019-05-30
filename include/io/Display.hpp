#include <cstdint>

#include <SFML/Graphics.hpp>

namespace chip8::io
{
    class DisplayPixels
    {
        public:
            using PixelValue_t = int;

            static const int kWidth_ = 64;
            static const int kHeight_ = 32;

            DisplayPixels();
            void Clear();

            class PixelColumn 
            {
                friend DisplayPixels;
                public:
                    PixelValue_t& operator[](std::size_t row)
                    {
                        return parent_.pixels_[col_][row];
                    }
                private:
                    PixelColumn(DisplayPixels &parent, std::size_t col) : 
                        parent_(parent), col_(col) {}
                    DisplayPixels& parent_;
                    std::size_t col_;
            };

            PixelColumn operator[](std::size_t row)
            {
                return PixelColumn(*this, row);
            }
        private:
            using PixelsColum_t = std::array<PixelValue_t, kHeight_>;
            using Pixels_t = std::array<PixelsColum_t, kWidth_>;
            Pixels_t pixels_;
    };

    class DisplayRenderer
    {
        public:
            explicit DisplayRenderer(DisplayPixels& displayPixels);
            void Update();
        private:
            DisplayPixels& displayPixels_;

            class TileMap : public sf::Drawable, public sf::Transformable
            {
                public:
                    bool Load(const std::string& tileset, sf::Vector2u tileSize, DisplayPixels& tiles, unsigned int width, unsigned int height);

                private:
                    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

                    sf::VertexArray m_vertices;
                    sf::Texture m_tileset;
            };
            TileMap tileMap_;

            sf::RenderWindow window_{sf::VideoMode(800, 600), "Chip8 Display"};
    };
}
