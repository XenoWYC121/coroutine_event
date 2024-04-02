//
// Created by 12992 on 2024/4/1.
//

#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/coroutine/promise_type.h"

namespace coroutine_async::coroutine
{
    event_coroutine::event_coroutine(const coroutine_handle<promise_type> &obj)
            : m_handler(obj)
    {

    }

    void event_coroutine::resume()
    {
        this->m_handler.resume();
    }

    event_coroutine::operator bool() const
    {
        return !this->m_handler.done();
    }

    void event_coroutine::set_fd(int fd)
    {
        this->m_handler.promise().set_fd(fd);
    }

    void event_coroutine::set_context(core::context &context)
    {
        this->m_handler.promise().set_context(context);
    }
}