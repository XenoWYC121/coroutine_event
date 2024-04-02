//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_EVENT_HPP
#define COROUTINE_ASYNC_EVENT_HPP


namespace coroutine_async::event
{



    class event
    {
    public:
        explicit event(int fd) : m_fd(fd) {}

        virtual ~event() = default;

        int get_fd() const { return this->m_fd; }

    private:
        int m_fd;
    };

}

#endif //COROUTINE_ASYNC_EVENT_HPP
