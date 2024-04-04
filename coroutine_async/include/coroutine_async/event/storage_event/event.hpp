//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_EVENT_HPP
#define COROUTINE_ASYNC_EVENT_HPP

#include <utility>

#include "coroutine_async/coroutine/event_coroutine.h"


namespace coroutine_async::event
{

    enum class event_type
    {
        READ, WRITE, ACCEPT, TIMER
    };


    class event
    {
    public:
        explicit event(int fd, event_type type, coroutine::event_coroutine cor)
                : m_fd(fd), type(type), m_coroutine(std::move(cor)) {}

        virtual ~event() = default;

        int get_fd() const { return this->m_fd; }

        event_type get_type() const { return this->type; }

        coroutine::event_coroutine &get_coroutine() { return this->m_coroutine; }

    private:
        int m_fd;
        event_type type;
        coroutine::event_coroutine m_coroutine;
    };

    class read_event
            : public event
    {
    public:
        read_event(int fd, coroutine::event_coroutine cor, size_t size, char *buffer)
                : event(fd, event_type::READ, std::move(cor)),
                  size(size), buffer(buffer) {}

        size_t get_size() const { return this->size; }

        char *get_buffer() { return this->buffer; }

    private:
        size_t size;
        char *buffer;
    };

    class write_event
            : public event
    {
    public:
        write_event(int fd, coroutine::event_coroutine cor, size_t size, const char *buffer)
                : event(fd, event_type::WRITE, std::move(cor)),
                  size(size), buffer(buffer) {}

        size_t get_size() const { return this->size; }

        const char *get_buffer() const { return this->buffer; }

    private:
        size_t size;
        const char *buffer;
    };


}

#endif //COROUTINE_ASYNC_EVENT_HPP
