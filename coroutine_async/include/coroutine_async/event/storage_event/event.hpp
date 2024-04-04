//
// Created by 12992 on 2024/4/2.
//

#ifndef COROUTINE_ASYNC_EVENT_HPP
#define COROUTINE_ASYNC_EVENT_HPP

#include <utility>
#include <arpa/inet.h>
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
        read_event(int fd, coroutine::event_coroutine cor, size_t size, char *buffer, int &error_code, size_t &res_size)
                : event(fd, event_type::READ, std::move(cor)),
                  size(size), buffer(buffer), error_code(&error_code), res_size(&res_size) {}

        size_t get_size() const { return this->size; }

        char *get_buffer() { return this->buffer; }

        void set_error_code(int value) { *this->error_code = value; }

        void set_res_size(size_t value) { *this->res_size = value; }

    private:
        size_t size;
        char *buffer;
        int *error_code;
        size_t *res_size;
    };

    class write_event
            : public event
    {
    public:
        write_event(int fd, coroutine::event_coroutine cor, size_t size, const char *buffer, int &error_code,
                    size_t &res_size)
                : event(fd, event_type::WRITE, std::move(cor)),
                  size(size), buffer(buffer), error_code(&error_code), res_size(&res_size) {}

        size_t get_size() const { return this->size; }

        const char *get_buffer() const { return this->buffer; }

        void set_error_code(int value) { *this->error_code = value; }

        void set_res_size(size_t value) { *this->res_size = value; }

    private:
        size_t size;
        const char *buffer;
        int *error_code;
        size_t *res_size;
    };

    class accept_event
            : public event
    {
    public:
        accept_event(int fd, coroutine::event_coroutine cor, int &sock_fd, sockaddr_in &addr, int &error_code)
                : event(fd, event_type::ACCEPT, std::move(cor)), sock_fd(&sock_fd), addr(&addr),
                  error_code(&error_code) {};

        void set_sock_fd(int value) { *this->sock_fd = value; }

        void set_sockaddr(const sockaddr_in &addr1) { *this->addr = addr1; }

        void set_error_code(int value) { *this->error_code = value; }

    private:
        int *sock_fd;
        sockaddr_in *addr;
        int *error_code;
    };


}

#endif //COROUTINE_ASYNC_EVENT_HPP
