//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_ASYNC_TIMER_H
#define COROUTINE_ASYNC_ASYNC_TIMER_H


#include <queue>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <vector>

namespace coroutine_async::event
{
    class timer_event;
}
namespace coroutine_async::core
{
    class context;
}


namespace coroutine_async::core
{
    using namespace std;

    using heap_type = priority_queue<event::timer_event, vector<event::timer_event>, std::greater<>>;

    class async_timer
    {
    public:
        explicit async_timer(core::context &context);

        ~async_timer();

        void new_timer_event(const event::timer_event &event);

        void stop();

        void shutdown();

    private:
        void run_thread();

        void notify_context(const event::timer_event &event);

    private:
        heap_type m_heap;
        mutex m_lock_heap;
        condition_variable m_cv;
        atomic<bool> is_stop{false};
        atomic<bool> is_shutdown{false};
        thread m_thread_handler;
        core::context &m_context;
    };

}

#endif //COROUTINE_ASYNC_ASYNC_TIMER_H
