//
// Created by 12992 on 2024/4/1.
//

#ifndef COROUTINE_ASYNC_EVENT_COROUTINE_H
#define COROUTINE_ASYNC_EVENT_COROUTINE_H

#include <iostream>
#include <coroutine>


namespace coroutine_async::core
{
    class context;
}

namespace coroutine_async::coroutine
{
    using namespace std;

    class promise_type;

    class event_coroutine
    {
    public:
        explicit event_coroutine(const coroutine_handle<promise_type> &obj);

        void set_fd(int fd);

        void set_context(core::context& context);

        void resume();

        explicit operator bool() const;

    private:
        coroutine_handle<promise_type> m_handler;
    };

}

#endif //COROUTINE_ASYNC_EVENT_COROUTINE_H
