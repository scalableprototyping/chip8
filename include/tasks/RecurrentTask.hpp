#ifndef CHIP8_RECURRENT_TASK_HPP
#define CHIP8_RECURRENT_TASK_HPP

#include <atomic>
#include <future>
#include <functional>

#include "timers/clock.hpp"

namespace chip8::tasks
{
    using TaskCallback = std::function<void(void)>;

    class RecurrentTask final
    {
        public:
            RecurrentTask(TaskCallback _callback, timers::Microseconds _sleep_time,
                          bool _auto_start = false);
            ~RecurrentTask();

            RecurrentTask(RecurrentTask&) = delete;
            void operator=(RecurrentTask&) = delete;

            void Start(bool _async = true);
            void Stop();
            bool IsRunning() const;

        private:
            void Loop();

        private:
            std::atomic<bool> stop_ { false };
            std::future<void> task_;

            const TaskCallback callback_;
            const timers::Microseconds sleep_time_;
    };
}

#endif
