//
// Created by 12992 on 2024/4/4.
//

#ifndef COROUTINE_ASYNC_EPOLL_CORE_H
#define COROUTINE_ASYNC_EPOLL_CORE_H

#include <arpa/inet.h>
#include <unordered_map>
#include <memory>
#include "core.hpp"

namespace coroutine_async::event
{
    class event;
}

namespace coroutine_async::core
{

    using namespace std;

    using event_ptr = unique_ptr<event::event>;

    class epoll_core
            : public core
    {
    public:
        explicit epoll_core(int black_hole);

        void add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor) override;

        void add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor) override;

        void add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor) override;

        void run() override;

    private:
        int ep_fd;
        unordered_map<int, event_ptr> event_map;
    };

} // core
// coroutine_async

#endif //COROUTINE_ASYNC_EPOLL_CORE_H
