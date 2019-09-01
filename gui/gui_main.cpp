#include <QApplication>
#include <QQmlContext>

// TODO: Enable for release build
//#include <QQmlApplicationEngine>
#include "liveReload/liveReloadQmlApplicationEngine.hpp"

#include "QInterpreter.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    // TODO: enable for release buidl
    //QQmlApplicationEngine qml_engine;
    chip8::liveReloadQmlApplicationEngine qml_engine;

    qml_engine.rootContext()->setContextProperty("qmlEngine", &qml_engine);

    chip8::QInterpreter chip8_interpreter;
    qml_engine.rootContext()->setContextProperty("chip8Interpreter", &chip8_interpreter);

    // TODO: qml_engine.load(QUrl("../gui/qml/main.qml"));
    qml_engine.load(QUrl(qgetenv("MAIN_QML")));
    // TODO: Enable this for release build
    //qml_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
