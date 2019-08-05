#include <QDir>

#include "QInterpreter.hpp"

namespace chip8
{
    QInterpreter::QInterpreter(QObject* _parent) : QObject(_parent)
    {}

    void QInterpreter::LoadRom(const QUrl& _path)
    {
        //TODO: log errors
        if(!_path.isLocalFile()) { return; }

        interpreter_.LoadRom(QDir::toNativeSeparators(_path.toLocalFile()).toStdString());
        interpreter_.StartRom();
    }
}
