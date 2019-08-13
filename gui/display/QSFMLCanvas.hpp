#pragma once
#ifndef CHIP_8_Q_SFML_CANVAS_HPP
#define CHIP_8_Q_SFML_CANVAS_HPP

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

namespace chip8 
{
    class QSFMLCanvas : public QWidget, public sf::RenderWindow
    {
        public :

            QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);

            virtual ~QSFMLCanvas() { };

        private :

            virtual void OnInit() = 0;

            virtual void OnUpdate() = 0;

            virtual QPaintEngine* paintEngine() const override;

            virtual void showEvent(QShowEvent*) override;

            virtual void paintEvent(QPaintEvent*) override;

            QTimer myTimer;
            bool   myInitialized;
    };
}
#endif
