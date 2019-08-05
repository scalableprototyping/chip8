#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "QInterpreter.hpp"

int main(int argc, char** argv)
{
    chip8::QInterpreter chip8_interpreter;

    QApplication app(argc, argv);

    QQmlApplicationEngine qml_engine;
    qml_engine.rootContext()->setContextProperty("interpreter", &chip8_interpreter);
    qml_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
