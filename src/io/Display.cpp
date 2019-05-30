#include "io/Display.hpp"

#include <iostream>

namespace chip8::io
{
    DisplayPixels::DisplayPixels() 
    {
        Clear();
    }

    void DisplayPixels::Clear() {
        for (auto& col : pixels_) 
        {
            col.fill(0);
        }
    }

    DisplayRenderer::DisplayRenderer(DisplayPixels& displayPixels) :
        displayPixels_(displayPixels),
        tileMap_(displayPixels_)
    {
        const int kMapWidth = displayPixels.kWidth_*tileMap_.kTextureWidth_;
        const int kMapHeight = displayPixels.kHeight_*tileMap_.kTextureHeight_;

        tileMap_.setScale(
            float(window_.getSize().x) / kMapWidth, 
            float(window_.getSize().y) / kMapHeight
            );
    }

    void DisplayRenderer::Update() 
    {
        if (window_.isOpen()) 
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window_.close();
            }

            tileMap_.Update();
            window_.clear();
            window_.draw(tileMap_);
            window_.display();
        }
    }

    DisplayRenderer::TileMap::TileMap(DisplayPixels& displayPixels) : 
        displayPixels_(displayPixels)
    {
        if (!tileSetTexture_.loadFromFile(kTileSetTexturePath_))
        {
            // TODO: Error handling
        }
        vertices_.setPrimitiveType(sf::Quads);
        const int kNumberOfVerticesPerQuad = 4;
        vertices_.resize(displayPixels_.kWidth_ * displayPixels_.kHeight_ * kNumberOfVerticesPerQuad);
    }

    void DisplayRenderer::TileMap::Update() 
    {
        for (unsigned int i = 0; i < displayPixels_.kWidth_; ++i)
            for (unsigned int j = 0; j < displayPixels_.kHeight_; ++j)
            {
                const int pixelValue = displayPixels_[i][j];

                // Find its position in the tileset texture
                const int tu = pixelValue % (tileSetTexture_.getSize().x / kTextureWidth_);
                const int tv = pixelValue / (tileSetTexture_.getSize().x / kTextureWidth_);

                // Get a pointer to the current tile's quad
                sf::Vertex* quad = &vertices_[(i + j * displayPixels_.kWidth_) * 4];

                // Define its 4 corners
                quad[0].position = sf::Vector2f(i * kTextureWidth_, j * kTextureHeight_);
                quad[1].position = sf::Vector2f((i + 1) * kTextureWidth_, j * kTextureHeight_);
                quad[2].position = sf::Vector2f((i + 1) * kTextureWidth_, (j + 1) * kTextureHeight_);
                quad[3].position = sf::Vector2f(i * kTextureWidth_, (j + 1) * kTextureHeight_);

                // Define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * kTextureWidth_, tv * kTextureHeight_);
                quad[1].texCoords = sf::Vector2f((tu + 1) * kTextureWidth_, tv * kTextureHeight_);
                quad[2].texCoords = sf::Vector2f((tu + 1) * kTextureWidth_, (tv + 1) * kTextureHeight_);
                quad[3].texCoords = sf::Vector2f(tu * kTextureWidth_, (tv + 1) * kTextureHeight_);
            }
    }

    void DisplayRenderer::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &tileSetTexture_;
        target.draw(vertices_, states);
    }
}
