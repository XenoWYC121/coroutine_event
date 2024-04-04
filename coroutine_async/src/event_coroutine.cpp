//
// Created by 12992 on 2024/4/1.
//

#include "coroutine_async/coroutine/event_coroutine.h"

namespace coroutine_async::coroutine
{
    event_coroutine::event_coroutine(shared_ptr<context_object> co_context)
            : m_context(std::move(co_context))
    {

    }

    void event_coroutine::resume()
    {
        this->m_context->m_handler.resume();
    }

    event_coroutine::operator bool() const
    {
        return !this->m_context->m_handler.done();
    }

    bool event_coroutine::operator==(const event_coroutine &cor)
    {
        return this->m_context.get() == cor.m_context.get();
    }

}