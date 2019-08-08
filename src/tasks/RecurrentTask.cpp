#include "tasks/RecurrentTask.hpp"

namespace chip8::tasks
{
    RecurrentTask::RecurrentTask(TaskCallback _callback, timers::Microseconds _sleep_time,
                                 bool _auto_start) :
       callback_   { _callback },
       sleep_time_ { _sleep_time }
    {
        if(_auto_start) { Start(); }
    }

    RecurrentTask::~RecurrentTask()
    {
        stop_ = true;

        try
        {
            task_.wait();
        }
        catch(const std::future_error&) {}
    }

    void RecurrentTask::Loop()
    {
        using namespace timers;

        while(!stop_)
        {
            callback_();
            std::this_thread::sleep_for(sleep_time_);
        }
    }

    void RecurrentTask::Stop()
    {
        stop_ = true;

        try
        {
            task_.get();
        }
        catch(const std::future_error&) {}
    }

    void RecurrentTask::Start(bool _async)
    {
        Stop();

        stop_ = false;

        if(_async)
        {
            task_ = std::async(std::launch::async, &RecurrentTask::Loop, this);
        }
        else
        {
            task_ = std::async(std::launch::deferred, &RecurrentTask::Loop, this);
            task_.wait();
        }
    }

    bool RecurrentTask::IsRunning() const
    {
        return task_.valid();
    }
}
