//
// Created by 12992 on 2024/4/4.
//

#include "coroutine_async/context/epoll_core.h"
#include <sys/epoll.h>

namespace coroutine_async::core
{
    epoll_core::epoll_core(int black_hole)
            : core(black_hole), ep_fd(epoll_create1(1))
    {

    }

    void epoll_core::add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor)
    {

    }

    void epoll_core::add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor)
    {

    }

    void epoll_core::add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor)
    {

    }

    void epoll_core::run()
    {

    }


}