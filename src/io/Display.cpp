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
        displayPixels_(displayPixels)
    {
        const int kTextureHeight = 32;
        const int kTextureWidth = 32;
        const int kMapWidth = displayPixels.kWidth_*kTextureWidth;
        const int kMapHeight = displayPixels.kHeight_*kTextureHeight;
        if (!tileMap_.Load("../assets/tileset.png", sf::Vector2u(kTextureWidth, kTextureHeight), displayPixels_, displayPixels.kWidth_, displayPixels.kHeight_))
        {
            // TODO: improve exection handling
        }

        tileMap_.setScale(
            float(window_.getSize().x) / kMapWidth, 
            float(window_.getSize().y) / kMapHeight
            );
    }

    void DisplayRenderer::Update() 
    {
        if (window_.isOpen()) 
        {
            // handle events
            sf::Event event;
            while (window_.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window_.close();
            }

            // draw the map
            window_.clear();
            window_.draw(tileMap_);
            window_.display();
        }
    }

    bool DisplayRenderer::TileMap::Load(const std::string& tileset, sf::Vector2u tileSize, DisplayPixels& tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i][j];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

    void DisplayRenderer::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
}
