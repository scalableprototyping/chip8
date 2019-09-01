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

            Q_SLOT void loadRom(const QUrl& _path);

            Q_SLOT void setCpuFrequency(qreal _new_frequency);
            Q_SLOT void setTimersFrequency(qreal _new_frequency);

        private:
            std::unique_ptr<Interpreter> interpreter_;
    };
}

#endif
