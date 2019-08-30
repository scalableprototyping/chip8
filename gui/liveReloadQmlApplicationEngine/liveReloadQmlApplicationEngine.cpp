#include "liveReloadQmlApplicationEngine.h"

liveReloadQmlApplicationEngine::liveReloadQmlApplicationEngine(QObject *parent)
    : QQmlApplicationEngine(parent)
{

}

void liveReloadQmlApplicationEngine::clearCache()
{
    this->clearComponentCache();
}
