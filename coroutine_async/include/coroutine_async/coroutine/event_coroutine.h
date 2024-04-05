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

    class accept_info;

    class read_info;
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
        core::context *io_context{};
    };

    class event_coroutine
    {
    public:
        class promise_type;

        explicit event_coroutine(shared_ptr<context_object> co_context);

        void set_io_context(core::context &io_context);

        void resume();

        explicit operator bool() const;

        bool operator==(const event_coroutine &cor);

    private:
        shared_ptr<context_object> m_context;
    };

    class event_coroutine::promise_type
    {
    public:
        event_coroutine get_return_object();


        suspend_always initial_suspend() noexcept;

        suspend_never final_suspend() noexcept;

        suspend_always yield_value(util::info &&info1);

        void unhandled_exception() noexcept {}

    private:
        void handle_accept(util::accept_info &info);

        void handle_read(util::read_info& info);

        event_coroutine get_return_object_inside();


    private:
        shared_ptr<context_object> m_context;
    };

}

#endif //COROUTINE_ASYNC_EVENT_COROUTINE_H
