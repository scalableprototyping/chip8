#pragma once
#ifndef CHIP_8_Q_INTERPRETER_HPP
#define CHIP_8_Q_INTERPRETER_HPP

#include <QObject>
#include <QUrl>

#include "Interpreter.hpp"

#include <memory>

namespace chip8
{
    class QInterpreter : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QInterpreter)

        public:
            explicit QInterpreter(QObject* _parent = nullptr);
            ~QInterpreter() = default;

            Q_SLOT void LoadRom(const QUrl& _path);

            Q_SLOT void SetCpuFrequency(qreal _new_frequency);
            Q_SLOT void SetTimersFrequency(qreal _new_frequency);

            Q_SLOT bool GetPixelState(int _col, int _row);
            Q_SLOT auto GetDataRegister(int _reg);
            Q_SLOT auto GetIRegister();

            Q_SLOT void Play();
            Q_SLOT void Pause();
            Q_SLOT void Step();

        private:
            std::unique_ptr<Interpreter> interpreter_;
    };
}

#endif
