//
// Created by 12992 on 2024/4/1.
//


#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/util/info.hpp"

namespace coroutine_async::coroutine
{
    event_coroutine event_coroutine::promise_type::get_return_object()
    {
        auto ctx = make_shared<context_object>();
        ctx->m_handler = coroutine_handle<promise_type>::from_promise(*this);
        this->m_context = ctx;
        return event_coroutine(ctx);
    }

    suspend_always event_coroutine::promise_type::initial_suspend() noexcept
    {
        return {};
    }

    suspend_always event_coroutine::promise_type::final_suspend() noexcept
    {
        return {};
    }

    suspend_always event_coroutine::promise_type::yield_value(const util::info &info1)
    {
        return {};
    }

}