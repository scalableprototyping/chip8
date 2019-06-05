#include "io/display/Renderer.hpp"
#include "io/display/PixelArray.hpp"

#include <stdexcept>
#include <algorithm>
#include <iterator>

namespace chip8::io::display
{
    Renderer::Renderer(PixelArray& pixels) :
        pixels_(pixels),
        pixelQuads_(pixels_)
    {
        const int kMapWidth = pixels_.kWidth_*pixelQuads_.kTextureWidth_;
        const int kMapHeight = pixels_.kHeight_*pixelQuads_.kTextureHeight_;
        pixelQuads_.setScale(
            float(window_.getSize().x) / kMapWidth, 
            float(window_.getSize().y) / kMapHeight
            );
    }

    void Renderer::Update() 
    {
        if (window_.isOpen()) 
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window_.close();
            }

            pixelQuads_.Update();
            window_.clear();
            window_.draw(pixelQuads_);
            window_.display();
        }
    }

    Renderer::PixelQuads::PixelQuads(const PixelArray& pixels) :
        pixels_(pixels)
    {
        if (!pixelsTexture_.loadFromFile(kTileSetTexturePath_))
        {
            throw std::runtime_error("Could not open tilteset texture file.");
        }

        vertices_.setPrimitiveType(sf::Quads);
        const int kNumberOfVerticesPerQuad = 4;
        vertices_.resize(pixels_.kWidth_ * pixels_.kHeight_ * kNumberOfVerticesPerQuad);

        pixelOffTextureCoords = std::vector<sf::Vector2f>
        {
            sf::Vector2f(0, 0),
            sf::Vector2f(kTextureWidth_, 0),
            sf::Vector2f(kTextureWidth_, kTextureHeight_),
            sf::Vector2f(0, kTextureHeight_)
        };

        std::transform
        (
            pixelOffTextureCoords.begin(), pixelOffTextureCoords.end(),
            std::back_inserter(pixelOnTextureCoords),
            [this](auto v) {
                return v + sf::Vector2f(kTextureWidth_, 0);
        });

        pixelTextureCoords = pixelTextureCoords_t 
        { 
            pixelOffTextureCoords,
            pixelOnTextureCoords
        };
    }

    void Renderer::PixelQuads::Update() 
    {
        for (auto i = 0; i < pixels_.kWidth_; ++i)
            for (auto j = 0; j < pixels_.kHeight_; ++j)
            {
                // Get a pointer to the current tile's quad
                sf::Vertex* quad = &vertices_[(i + j*pixels_.kWidth_)*4];

                // Set Quad texture coordinates
                const auto pixelState = pixels_.at(i,j);
                quad[0].texCoords = pixelTextureCoords[pixelState][0];
                quad[1].texCoords = pixelTextureCoords[pixelState][1];
                quad[2].texCoords = pixelTextureCoords[pixelState][2];
                quad[3].texCoords = pixelTextureCoords[pixelState][3];

                // Define its 4 corners
                quad[0].position = sf::Vector2f(i * kTextureWidth_, j * kTextureHeight_);
                quad[1].position = sf::Vector2f((i + 1) * kTextureWidth_, j * kTextureHeight_);
                quad[2].position = sf::Vector2f((i + 1) * kTextureWidth_, (j + 1) * kTextureHeight_);
                quad[3].position = sf::Vector2f(i * kTextureWidth_, (j + 1) * kTextureHeight_);
            }
    }

    void Renderer::PixelQuads::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &pixelsTexture_;
        target.draw(vertices_, states);
    }
}
