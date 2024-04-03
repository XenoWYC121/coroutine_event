//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_CONTEXT_H
#define COROUTINE_ASYNC_CONTEXT_H

#include <iostream>
#include <memory>
#include <variant>
#include "async_timer.h"

namespace coroutine_async::event
{
    class read_event;
}


namespace coroutine_async::core
{
    class core;

    using event_type = variant<event::read_event>;

    class context
    {
    public:
        context(unique_ptr<core> core1);

        void new_event(const event_type &new_event);

    private:
        int black_hole_fd{-1};
        async_timer timer;
        unique_ptr<core> m_core;
    };
} // coroutine_async

#endif //COROUTINE_ASYNC_CONTEXT_H
