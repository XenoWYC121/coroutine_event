//
// Created by 12992 on 2024/4/4.
//

#include "coroutine_async/net/socket.h"
#include "coroutine_async/util/info.hpp"
#include <iostream>

namespace coroutine_async::net
{
    socket::socket(core::context& context)
            : m_context(&context),
              sock_fd(new int(-1), [](const int* ptr) -> void
              {
                  close(*ptr);
                  std::cout << "connection close" << std::endl;
              })
    {

    }

    util::read_info socket::async_read(char* buffer, size_t size, int& ec, size_t& res_size)
    {
        return {*this->sock_fd, buffer, size, ec, res_size};
    }

    util::write_info socket::async_write(const char* buffer, size_t size, int ec, size_t res_size)
    {
        return {*this->sock_fd, buffer, size, ec, res_size};
    }
}
