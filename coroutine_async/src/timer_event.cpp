//
// Created by 12992 on 2024/4/2.
//

#include "coroutine_async/event/storage_event/timer_event.h"


namespace coroutine_async::event
{
    bool operator<(const timer_event &n1, const timer_event &n2)
    {
        return n1.tp < n2.tp;
    }

    bool operator>(const timer_event &n1, const timer_event &n2)
    {
        return n1.tp > n2.tp;
    }

    const chrono::system_clock::time_point &timer_event::get_tp() const
    {
        return this->tp;
    }

}
// coroutine_async