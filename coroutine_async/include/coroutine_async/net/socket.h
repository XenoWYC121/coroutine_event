//
// Created by 12992 on 2024/4/4.
//

#ifndef COROUTINE_ASYNC_SOCKET_H
#define COROUTINE_ASYNC_SOCKET_H

#include <arpa/inet.h>
#include <memory>

namespace coroutine_async::core
{
    class context;
}

namespace coroutine_async::util
{
    class info;
    class read_info;
    class write_info;
}

namespace coroutine_async::net
{

    class acceptor;

    class socket
    {
        friend class acceptor;

    public:
        socket(core::context& context);

        util::read_info async_read(char* buffer, size_t size, int & ec, size_t & res_size);

        util::write_info async_write(const char* buffer, size_t size, int ec, size_t res_size);

    private:
        core::context* m_context;
        sockaddr_in addr;
        std::shared_ptr<int> sock_fd;
    };
}

#endif //COROUTINE_ASYNC_SOCKET_H
