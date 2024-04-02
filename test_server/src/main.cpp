//
// Created by 12992 on 2024/4/1.
//
#include <iostream>
#include "coroutine_async/context/async_timer.h"
#include "coroutine_async/context/context.h"
#include "coroutine_async/event/storage_event/timer_event.h"

using namespace std;

int main()
{
    coroutine_async::core::context context1;
    coroutine_async::core::async_timer timer(context1);
    timer.new_timer_event(coroutine_async::event::timer_event(10, 10s));
    this_thread::sleep_for(2s);
    timer.new_timer_event({10, 3s});
}