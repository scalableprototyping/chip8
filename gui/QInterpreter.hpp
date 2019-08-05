#ifndef CHIP_8_Q_INTERPRETER_HPP
#define CHIP_8_Q_INTERPRETER_HPP

#include <QObject>
#include <QUrl>

#include "Interpreter.hpp"

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

        private:
            Interpreter interpreter_;
    };
}

#endif
