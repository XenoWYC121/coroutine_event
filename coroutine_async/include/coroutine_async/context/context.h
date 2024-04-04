//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_CONTEXT_H
#define COROUTINE_ASYNC_CONTEXT_H

#include <iostream>
#include <memory>
#include <variant>
#include <arpa/inet.h>
#include <functional>

#include "async_timer.h"
#include "coroutine_async/coroutine/event_coroutine.h"

namespace coroutine_async::coroutine
{
    class event_coroutine;
}


namespace coroutine_async::core
{
    class core;


    class context
    {
    public:
        context(unique_ptr<core> core1);

        void add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                      size_t &res_size);

        void add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                       size_t &res_size);

        void
        add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor, int &error_code);

        void run();

        void start_coroutine(function<coroutine::event_coroutine()> cor);

    private:
        int black_hole_fd{-1};
        async_timer timer;
        unique_ptr<core> m_core;
    };
} // coroutine_async

#endif //COROUTINE_ASYNC_CONTEXT_H
