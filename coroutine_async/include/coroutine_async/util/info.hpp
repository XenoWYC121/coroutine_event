//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_INFO_HPP
#define COROUTINE_ASYNC_INFO_HPP

#include <arpa/inet.h>

namespace coroutine_async::util
{

    enum class info_type
    {
        READ,
        WRITE,
        ACCEPT,
        TIMER
    };

    class info
    {
    public:
        explicit info(info_type type) : type(type) {}

        virtual ~info() = default;

        info_type get_type() const { return this->type; }

    private:
        info_type type;
    };

    class accept_info
            : public info
    {
    public:
        accept_info(int fd, sockaddr_in &addr, int &sock_fd, int &ec)
                : info(info_type::ACCEPT), fd(fd), addr(&addr), sock_fd(&sock_fd), ec(&ec) {}

        int get_fd() const { return this->fd; }

        sockaddr_in &get_sock_addr() { return *this->addr; }

        int &get_sock_fd() { return *this->sock_fd; }

        int &get_ec() { return *this->ec; }

    private:
        int fd;
        sockaddr_in *addr;
        int *sock_fd;
        int *ec;

    };

}

#endif //COROUTINE_ASYNC_INFO_HPP
