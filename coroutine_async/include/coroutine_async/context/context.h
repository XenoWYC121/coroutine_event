//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_CONTEXT_H
#define COROUTINE_ASYNC_CONTEXT_H

#include <iostream>
#include <memory>
#include <variant>
#include <arpa/inet.h>
#include "async_timer.h"

namespace coroutine_async::event
{
    class read_event;
}


namespace coroutine_async::core
{
    class core;


    class context
    {
    public:
        context(unique_ptr<core> core1);

        void add_read(int fd, char *buffer, size_t size);

        void add_write(int fd, const char *buffer, size_t size);

        void add_accept(int fd, sockaddr_in &addr, int &sock_fd);

    private:
        int black_hole_fd{-1};
        async_timer timer;
        unique_ptr<core> m_core;
    };
} // coroutine_async

#endif //COROUTINE_ASYNC_CONTEXT_H
