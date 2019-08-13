#include <QDir>

#include "Interpreter.hpp"
#include "QInterpreter.hpp"

namespace chip8
{
    QInterpreter::QInterpreter(QObject* _parent) : QObject(_parent)
    {}

    void QInterpreter::loadRom(const QUrl& _path)
    {
        //TODO: log errors
        if(!_path.isLocalFile()) { return; }

        interpreter_ = std::make_unique<Interpreter>();

        interpreter_->LoadRom(QDir::toNativeSeparators(_path.toLocalFile()).toStdString());
        interpreter_->StartRom();
    }

    void QInterpreter::setCpuFrequency(qreal _new_frequency)
    {
        if (interpreter_)
        {
            timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
            interpreter_->SetCpuFrequency(frequency);
        }
    }

    void QInterpreter::setTimersFrequency(qreal _new_frequency)
    {
        if (interpreter_)
        {
            timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
            interpreter_->SetTimersFrequency(frequency);
        }
    }
}
