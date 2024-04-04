//
// Created by 12992 on 2024/4/4.
//

#ifndef COROUTINE_ASYNC_SOCKET_H
#define COROUTINE_ASYNC_SOCKET_H
#include <arpa/inet.h>

namespace coroutine_async::net
{

    class acceptor;

    class socket
    {
        friend class acceptor;

    public:

    private:
        sockaddr_in addr;
        int sock_fd;
    };
}

#endif //COROUTINE_ASYNC_SOCKET_H
