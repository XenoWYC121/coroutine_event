//
// Created by 12992 on 2024/4/4.
//

#include "coroutine_async/net/socket.h"


namespace coroutine_async::net
{
    socket::socket(core::context& context)
            : m_context(&context),
              sock_fd(new int(-1), [](const int* ptr) -> void
              {
                  delete ptr;
              })
    {

    }
}
