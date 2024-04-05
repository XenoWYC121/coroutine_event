//
// Created by 12992 on 2024/4/1.
//
#include <iostream>
#include "coroutine_async/coroutine_async.h"

using namespace std;

//using namespace coroutine_async::coroutine;
//using namespace coroutine_async;
//
//event_coroutine hello()
//{
//    cout << "before hello" << endl;
//    co_yield util::info{util::info_type::READ};
//    cout << "after hello" << endl;
//}

int main()
{
    using namespace coroutine_async;
    core::context context1(make_unique<core::epoll_core>(0));
    net::acceptor acceptor1(context1, "0.0.0.0", 25444);
    context1.start_coroutine([&acceptor1,&context1]() -> coroutine::event_coroutine
                             {
                                 net::socket n1{context1};
                                 int ec{0};
                                 co_yield acceptor1.async_accept(n1, ec);
                                 cout << "get new connection!" << endl;
                             });
    context1.run();
}