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

    void QInterpreter::SetCpuFrequency(qreal _new_frequency)
    {
        timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
        interpreter_.SetCpuFrequency(frequency);
    }

    void QInterpreter::SetTimersFrequency(qreal _new_frequency)
    {
        timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
        interpreter_.SetTimersFrequency(frequency);
    }
}
