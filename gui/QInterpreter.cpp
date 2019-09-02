#include <QDir>

#include "Interpreter.hpp"
#include "QInterpreter.hpp"

namespace chip8
{
    QInterpreter::QInterpreter(QObject* _parent) : QObject(_parent)
    {}

    void QInterpreter::LoadRom(const QUrl& _path)
    {
        //TODO: log errors
        if(!_path.isLocalFile()) { return; }

        interpreter_ = std::make_unique
            <
                Interpreter
                <
                    io::display::DisplayRenderingPolicyDoNothing 
                >
            >();

        interpreter_->LoadRom(QDir::toNativeSeparators(_path.toLocalFile()).toStdString());
        interpreter_->StartRom();
    }

    void QInterpreter::SetCpuFrequency(qreal _new_frequency)
    {
        if (interpreter_)
        {
            timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
            interpreter_->SetCpuFrequency(frequency);
        }
    }

    void QInterpreter::SetTimersFrequency(qreal _new_frequency)
    {
        if (interpreter_)
        {
            timers::Frequency frequency { static_cast<uint64_t>(_new_frequency) };
            interpreter_->SetTimersFrequency(frequency);
        }
    }

    bool QInterpreter::GetPixelState(int _col, int _row)
    {
        if (interpreter_)
        {
            return interpreter_->pixels_.at(_col, _row);
        }
        return false;
    }

    auto QInterpreter::GetDataRegister(int _reg)
    {
        return interpreter_->data_registers_[_reg].Get();
    }

    auto QInterpreter::GetIRegister()
    {
        return interpreter_->i_register_.Get();
    }

    void QInterpreter::Play()
    {
        if (interpreter_)
        {
            interpreter_->Continue();
        }
    }

    void QInterpreter::Pause()
    {
        if (interpreter_)
        {
            interpreter_->Pause();
        }
    }

    void QInterpreter::Step()
    {
        if (interpreter_)
        {
            interpreter_->Step();
        }
    }

}
