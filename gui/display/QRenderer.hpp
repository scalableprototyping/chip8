#pragma once
#ifndef CHIP_8_Q_RENDERER_HPP
#define CHIP_8_Q_RENDERER_HPP

#include "QSFMLCanvas.hpp"

namespace chip8 
{
    class QRenderer final : public QSFMLCanvas
    {
        public :
            QRenderer(QWidget* Parent, const QPoint& Position, const QSize& Size);
            ~QRenderer() = default;
        private :
            virtual void OnInit() override;
            virtual void OnUpdate() override;

            sf::Texture myImage;
            sf::Sprite mySprite;
            sf::Clock clock_;
    };
}

#endif
