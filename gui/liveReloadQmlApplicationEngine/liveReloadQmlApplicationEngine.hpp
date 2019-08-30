#pragma once

#include <QQmlApplicationEngine>

class liveReloadQmlApplicationEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit liveReloadQmlApplicationEngine(QObject *parent = nullptr);

    Q_INVOKABLE void clearCache();
};
