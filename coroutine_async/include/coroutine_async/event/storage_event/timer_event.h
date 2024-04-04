//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_TIMER_EVENT_H
#define COROUTINE_ASYNC_TIMER_EVENT_H

#include "event.hpp"

#include <iostream>
#include <chrono>

namespace coroutine_async::event
{
    using namespace std;

    class timer_event
            : public event
    {
        friend bool operator<(const timer_event &n1, const timer_event &n2);

        friend bool operator>(const timer_event &n1, const timer_event &n2);

    public:
        template<typename TYPE>
        timer_event(int fd, coroutine::event_coroutine cor, const chrono::duration<int64_t, TYPE> &duration);


        const chrono::system_clock::time_point &get_tp() const;

    private:
        chrono::system_clock::time_point tp;
    };

    template<typename TYPE>
    timer_event::timer_event(int fd, coroutine::event_coroutine cor, const chrono::duration<int64_t, TYPE> &duration)
            :event(fd, event_type::TIMER, std::move(cor)), tp(duration + chrono::system_clock::now())
    {
    }

}

#endif //COROUTINE_ASYNC_TIMER_EVENT_H
