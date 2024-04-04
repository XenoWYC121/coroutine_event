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

}