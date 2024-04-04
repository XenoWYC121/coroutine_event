//
// Created by 12992 on 2024/4/1.
//


#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/context/context.h"
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

    suspend_never event_coroutine::promise_type::final_suspend() noexcept
    {
        return {};
    }

    suspend_always event_coroutine::promise_type::yield_value(util::info &&info1)
    {
        switch (info1.get_type())
        {
            case util::info_type::READ:
                break;
            case util::info_type::WRITE:
                break;
            case util::info_type::ACCEPT:
                this->handle_accept(dynamic_cast<util::accept_info &>(info1));
                break;
            case util::info_type::TIMER:
                break;
        }
        return {};
    }

    void event_coroutine::promise_type::handle_accept(util::accept_info &info)
    {
        this->m_context->io_context->add_accept(info.get_fd(), info.get_sock_addr(), info.get_sock_fd(),
                                                this->get_return_object_inside(), info.get_ec());
    }

    event_coroutine event_coroutine::promise_type::get_return_object_inside()
    {
        return event_coroutine(this->m_context);
    }

}