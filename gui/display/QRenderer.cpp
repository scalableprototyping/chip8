#include "QRenderer.hpp"

namespace chip8
{
    QRenderer::QRenderer(QWidget* Parent, const QPoint& Position, const QSize& Size) :
        QSFMLCanvas(Parent, Position, Size)
    {

    }

    void QRenderer::OnInit()
    {
        // Load the image
        myImage.loadFromFile("/home/woowapdabug/downloads/profile.png");

        // Setup the sprite
        mySprite.setTexture(myImage);
    }

    void QRenderer::OnUpdate()
    {
        // Clear screen
        //clear(sf::Color(0, 128, 0));

        // Rotate the sprite
        //mySprite.rotate(clock_.restart().asMilliseconds() * 100.f);

        // Draw it
        draw(mySprite);
    }
}
