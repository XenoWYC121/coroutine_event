//
// Created by 12992 on 2024/4/2.
//

#include "coroutine_async/context/async_timer.h"
#include "coroutine_async/event/storage_event/timer_event.h"

namespace coroutine_async::core
{
    void async_timer::new_timer_event(const event::timer_event& event)
    {
        lock_guard guard(this->m_lock_heap);
        this->m_heap.push(event);
        this->m_cv.notify_one();
    }

    async_timer::async_timer(context& context, int black_hole)
            : m_context(context), black_hole_fd(black_hole)
    {
        this->m_thread_handler = thread([this]()
                                        {
                                            this->run_thread();
                                        });
    }

    void async_timer::run_thread()
    {
        while (true)
        {
            unique_lock lock(this->m_lock_heap);
            if (this->m_heap.empty())
            {
                this->m_cv.wait(
                        lock,
                        [this]() -> bool
                        {
                            return this->is_stop || this->is_shutdown || !this->m_heap.empty();
                        });
            }
            if (this->is_shutdown)
            {
                return;
            }
            if (this->is_stop && this->m_heap.empty())
            {
                return;
            }
            auto res = this->m_cv.wait_until(lock, this->m_heap.top().get_tp());
            if (this->is_shutdown)
            {
                return;
            }
            if (this->is_stop && this->m_heap.empty())
            {
                return;
            }
            //时间耗尽
            if (res == std::cv_status::timeout)
            {
                //取出堆顶元素
                auto e1 = this->m_heap.top();
                this->m_heap.pop();
                lock.unlock();
                this->notify_context(e1);
            }
        }
    }

    void async_timer::notify_context(const event::timer_event& event)
    {
        cout << "timeout!" << endl;
    }

    void async_timer::stop()
    {
        this->is_stop = true;
        this->m_cv.notify_one();
        if (this->m_thread_handler.joinable())
        {
            this->m_thread_handler.join();
        }
    }

    void async_timer::shutdown()
    {
        this->is_shutdown = true;
        this->m_cv.notify_one();
        if (this->m_thread_handler.joinable())
        {
            this->m_thread_handler.join();
        }
    }

    async_timer::~async_timer()
    {
        this->stop();
    }
}