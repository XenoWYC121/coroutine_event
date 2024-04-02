//
// Created by 12992 on 2024/4/1.
//

#ifndef COROUTINE_ASYNC_PROMISE_TYPE_H
#define COROUTINE_ASYNC_PROMISE_TYPE_H

#include <coroutine>

namespace coroutine_async::util
{
    class info_type;
}
namespace coroutine_async::core
{
    class context;
}


namespace coroutine_async::coroutine
{

    class event_coroutine;

    using namespace std;

    class promise_type
    {
    public:
        event_coroutine get_return_object();

        suspend_always initial_suspend() noexcept;

        suspend_always final_suspend() noexcept;

        suspend_always yield_value(const util::info_type &info);

        void unhandled_exception() noexcept {}

        void set_fd(int fd);

        int get_fd() const;

        void set_context(core::context& context);

    private:
        int m_fd{-1};
        core::context *m_context{nullptr};
    };

} // coroutine
// coroutine_async

#endif //COROUTINE_ASYNC_PROMISE_TYPE_H
