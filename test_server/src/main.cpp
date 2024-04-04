//
// Created by 12992 on 2024/4/1.
//
#include <iostream>
#include "coroutine_async/context/async_timer.h"
#include "coroutine_async/context/context.h"
#include "coroutine_async/event/storage_event/timer_event.h"
#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/util/info.hpp"

using namespace std;

using namespace coroutine_async::coroutine;
using namespace coroutine_async;

event_coroutine hello()
{
    cout << "before hello" << endl;
    co_yield util::info{util::info_type::READ};
    cout << "after hello" << endl;
}

int main()
{
    auto c = hello();
    auto d = hello();
    c.resume();
    c.resume();
    d.resume();
    d.resume();
//    coroutine_async::core::context context1;
//    coroutine_async::core::async_timer timer(context1);
//    timer.new_timer_event(coroutine_async::event::timer_event(10, 5s));
//    this_thread::sleep_for(20s);
//    timer.new_timer_event(coroutine_async::event::timer_event(10, 5s));
//    timer.new_timer_event({10, 3s});
}