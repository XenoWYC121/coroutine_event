//
// Created by 12992 on 2024/4/1.
//

#include "coroutine_async/coroutine/promise_type.h"
#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/util/info.hpp"

namespace coroutine_async::coroutine
{
    event_coroutine promise_type::get_return_object()
    {
        return event_coroutine{coroutine_handle<promise_type>::from_promise(*this)};
    }

    suspend_always promise_type::initial_suspend() noexcept
    {
        return {};
    }

    suspend_always promise_type::final_suspend() noexcept
    {
        return {};
    }

    suspend_always promise_type::yield_value(const util::info_type &info)
    {
        return {};
    }

    void promise_type::set_fd(int fd)
    {
        this->m_fd = fd;
    }

    int promise_type::get_fd() const
    {
        return this->m_fd;
    }

    void promise_type::set_context(core::context &context)
    {
        this->m_context = &context;
    }
}