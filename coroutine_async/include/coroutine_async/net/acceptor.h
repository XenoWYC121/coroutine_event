//
// Created by 12992 on 2024/4/4.
//

#ifndef COROUTINE_ASYNC_ACCEPTOR_H
#define COROUTINE_ASYNC_ACCEPTOR_H


#include <iostream>


namespace coroutine_async::core
{
    class context;
}
namespace coroutine_async::util
{
    class info;
    class accept_info;
}

namespace coroutine_async::net
{
    using namespace std;

    class socket;

    class acceptor
    {
    public:
        explicit acceptor(core::context &context, const string &address, unsigned short port);

        util::accept_info async_accept(net::socket& socket1, int& ec);


    private:
        core::context *m_context;
        int acc_fd{-1};
    };

}

#endif //COROUTINE_ASYNC_ACCEPTOR_H
