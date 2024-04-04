//
// Created by 12992 on 2024/4/1.
//

#ifndef COROUTINE_ASYNC_EVENT_COROUTINE_H
#define COROUTINE_ASYNC_EVENT_COROUTINE_H

#include <iostream>
#include <coroutine>
#include <memory>

namespace coroutine_async::util
{
    class info;
}


namespace coroutine_async::core
{
    class context;
}

namespace coroutine_async::coroutine
{
    using namespace std;

    struct context_object
    {
        coroutine_handle<> m_handler;
    };

    class event_coroutine
    {
    public:
        class promise_type;

        explicit event_coroutine(shared_ptr<context_object> co_context);

        void resume();

        explicit operator bool() const;

    private:
        shared_ptr<context_object> m_context;
    };

    class event_coroutine::promise_type
    {
    public:
        event_coroutine get_return_object();

        suspend_always initial_suspend() noexcept;

        suspend_always final_suspend() noexcept;

        suspend_always yield_value(const util::info &info1);

        void unhandled_exception() noexcept {}

    private:
        shared_ptr<context_object> m_context;
    };

}

#endif //COROUTINE_ASYNC_EVENT_COROUTINE_H
