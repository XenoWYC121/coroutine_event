//
// Created by 12992 on 2024/4/3.
//

#ifndef COROUTINE_ASYNC_CORE_HPP
#define COROUTINE_ASYNC_CORE_HPP

namespace coroutine_async::coroutine
{
    class event_coroutine;
}

namespace coroutine_async::core
{

    class core
    {
    public:
        explicit core(int black_hole) : black_hole(black_hole) {}

        virtual ~core() = default;

        void set_black_hole(int fd) { this->black_hole = fd; }

        int get_black_hole() const { return this->black_hole; }


        virtual void add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                              size_t & res_size) = 0;

        virtual void
        add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                  size_t &res_size) = 0;

        virtual void
        add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor, int &error_code) = 0;

        virtual void run() = 0;

    private:
        int black_hole{-1};
    };
}

#endif //COROUTINE_ASYNC_CORE_HPP
