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

        void add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                      size_t & res_size) override;

        void add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                       size_t &res_size) override;

        void add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor,
                        int &error_code) override;

        void run() override;

    private:
        bool is_same_read_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor);

        bool is_same_write_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor);

        void new_read_event(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                            size_t &res_size);

        void
        new_write_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                        size_t &res_size);

        void new_accept_event(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor,
                              int &error_code);

        void remove_event(int fd);

        void handle_read_event(event::event &event1);

        void handle_write_event(event::event &event1);

        void handle_accept_event(event::event &event1);

        void handle_timer_event(event::event &event1);

    private:
        int ep_fd;
        unordered_map<int, event_ptr> event_map;
        inline static thread_local bool flag{false};
    };

} // core
// coroutine_async

#endif //COROUTINE_ASYNC_EPOLL_CORE_H
