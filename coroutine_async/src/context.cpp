//
// Created by 12992 on 2024/4/2.
//

#include "coroutine_async/context/context.h"
#include "coroutine_async/context/core.hpp"


#include <sys/fcntl.h>

namespace coroutine_async::core
{
    context::context(unique_ptr<core> core1)
            : black_hole_fd(open("/dev/null", O_WRONLY)),
              timer(*this, this->black_hole_fd),
              m_core(std::move(core1))
    {
        this->m_core->set_black_hole(this->black_hole_fd);
    }

    void context::add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                           size_t &res_size)
    {
        this->m_core->add_read(fd, buffer, size, cor, error_code, res_size);
    }

    void
    context::add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                       size_t &res_size)
    {
        this->m_core->add_write(fd, buffer, size, cor, error_code, res_size);
    }

    void
    context::add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor, int &error_code)
    {
        this->m_core->add_accept(fd, addr, sock_fd, cor, error_code);
    }

    void context::run()
    {
        this->m_core->run();
    }


}