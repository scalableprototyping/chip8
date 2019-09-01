#include "liveReloadQmlApplicationEngine.hpp"

namespace chip8
{
    liveReloadQmlApplicationEngine::liveReloadQmlApplicationEngine(QObject *parent)
        : QQmlApplicationEngine(parent)
    {}

    void liveReloadQmlApplicationEngine::clearCache()
    {
        this->clearComponentCache();
    }
}
