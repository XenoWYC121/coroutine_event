//
// Created by 12992 on 2024/4/4.
//

#include "coroutine_async/net/acceptor.h"
#include "coroutine_async/net/socket.h"
#include "coroutine_async/context/context.h"
#include "coroutine_async/util/info.hpp"
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>

namespace coroutine_async::net
{
    acceptor::acceptor(core::context &context, const string &address, unsigned short port)
            : m_context(&context), acc_fd(::socket(AF_INET, SOCK_STREAM, 0))
    {
        if (this->acc_fd < 0)
        {
            throw runtime_error(strerror(errno));
        }
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(address.data());
        addr.sin_port = htons(port);
        socklen_t socklen = sizeof(addr);
        int res = bind(this->acc_fd, reinterpret_cast<sockaddr *>(&addr), socklen);
        if (res < 0)
        {
            throw runtime_error(strerror(errno));
        }
        res = listen(this->acc_fd, 128);
        if (res < 0)
        {
            throw runtime_error(strerror(errno));
        }
    }

    util::accept_info acceptor::async_accept(net::socket &socket1, int &ec)
    {
        return {this->acc_fd, socket1.addr, *socket1.sock_fd, ec};
    }
}