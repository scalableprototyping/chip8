#pragma once
#ifndef CHIP_8_LIVE_RELOAD_QML_APPLICATION_ENGINE_HPP
#define CHIP_8_LIVE_RELOAD_QML_APPLICATION_ENGINE_HPP

#include <QQmlApplicationEngine>

namespace chip8
{
    class liveReloadQmlApplicationEngine : public QQmlApplicationEngine
    {
        Q_OBJECT
    public:
        explicit liveReloadQmlApplicationEngine(QObject *parent = nullptr);
        ~liveReloadQmlApplicationEngine() = default;

        Q_INVOKABLE void clearCache();
    };
}

#endif
