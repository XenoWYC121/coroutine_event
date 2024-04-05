//
// Created by 12992 on 2024/4/4.
//

#include "coroutine_async/context/epoll_core.h"
#include "coroutine_async/coroutine/event_coroutine.h"
#include "coroutine_async/event/storage_event/event.hpp"
#include <sys/epoll.h>
#include <cerrno>
#include <cstring>

namespace coroutine_async::core
{
    epoll_core::epoll_core(int black_hole)
            : core(black_hole), ep_fd(epoll_create(1))
    {
        if (ep_fd == -1)
        {
            throw runtime_error(strerror(errno));
        }
    }

    void epoll_core::add_read(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor, int &error_code,
                              size_t & res_size)
    {
        auto it = this->event_map.find(fd);
        if (this->event_map.end() == it)
        {
            //不存在
            this->new_read_event(fd, buffer, size, cor, error_code, res_size);
        }
        else if (!this->is_same_read_event(fd, buffer, size, cor))
        {
            //改变了
            auto copy_cor = cor;
            this->remove_event(fd);
            this->new_read_event(fd, buffer, size, copy_cor, error_code, res_size);
        }
        flag = true;
    }

    void epoll_core::add_write(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor,
                               int &error_code,
                               size_t &res_size)
    {
        auto it = this->event_map.find(fd);
        if (this->event_map.end() == it)
        {
            this->new_write_event(fd, buffer, size, cor, error_code, res_size);
        }
        else if (!this->is_same_write_event(fd, buffer, size, cor))
        {
            auto copy_cor = cor;
            this->remove_event(fd);
            this->new_write_event(fd, buffer, size, copy_cor, error_code, res_size);
        }
        flag = true;
    }

    void epoll_core::add_accept(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor,
                                int &error_code)
    {
        auto it = this->event_map.find(fd);
        if (this->event_map.end() == it)
        {
            this->new_accept_event(fd, addr, sock_fd, cor, error_code);
        }
        else
        {
            auto copy_cor = cor;
            this->remove_event(fd);
            this->new_accept_event(fd, addr, sock_fd, cor, error_code);
        }
        flag = true;
    }

    void epoll_core::run()
    {
        while (!this->event_map.empty())
        {
            array<epoll_event, 128> events{};
            int res = epoll_wait(this->ep_fd, &events[0], 128, -1);
            if (res == -1)
            {
                perror("wait");
                throw runtime_error(strerror(errno));
            }
            for (int i = 0; i < res; i++)
            {
                flag = false;
                auto it = this->event_map.find(events[i].data.fd);
                if (it == this->event_map.end())
                {
                    throw runtime_error("no fd!");
                }
                switch (it->second->get_type())
                {
                    using namespace event;
                    case event_type::READ:
                        this->handle_read_event(*it->second);
                        break;
                    case event_type::WRITE:
                        this->handle_write_event(*it->second);
                        break;
                    case event_type::ACCEPT:
                        this->handle_accept_event(*it->second);
                        break;
                    case event_type::TIMER:
                        this->handle_timer_event(*it->second);
                        break;
                }
                if (!flag)
                {
                    this->remove_event(it->first);
                }
            }
        }
    }

    bool epoll_core::is_same_read_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor)
    {
        auto it = this->event_map.find(fd);
        if (it == this->event_map.end())
        {
            return false;
        }
        if (it->second->get_type() != event::event_type::READ)
        {
            return false;
        }
        auto e = dynamic_cast<event::read_event *>(it->second.get());
        return e->get_buffer() == buffer && e->get_size() == size && e->get_coroutine() == cor;
    }

    bool epoll_core::is_same_write_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor)
    {
        auto it = this->event_map.find(fd);
        if (it == this->event_map.end())
        {
            return false;
        }
        if (it->second->get_type() != event::event_type::WRITE)
        {
            return false;
        }
        auto e = dynamic_cast<event::write_event *>(it->second.get());
        return e->get_buffer() == buffer && e->get_size() == size && e->get_coroutine() == cor;
    }

    void epoll_core::new_read_event(int fd, char *buffer, size_t size, const coroutine::event_coroutine &cor,
                                    int &error_code,
                                    size_t &res_size)
    {
        epoll_event ee{};
        ee.data.fd = fd;
        ee.events = EPOLLIN;
        epoll_ctl(this->ep_fd, EPOLL_CTL_ADD, fd, &ee);
        this->event_map.emplace(fd, make_unique<event::read_event>(fd, cor, size, buffer, error_code, res_size));
    }

    void epoll_core::new_write_event(int fd, const char *buffer, size_t size, const coroutine::event_coroutine &cor,
                                     int &error_code,
                                     size_t &res_size)
    {
        epoll_event ee{};
        ee.data.fd = fd;
        ee.events = EPOLLOUT;
        epoll_ctl(this->ep_fd, EPOLL_CTL_ADD, fd, &ee);
        this->event_map.emplace(fd, make_unique<event::write_event>(fd, cor, size, buffer, error_code, res_size));
    }

    void epoll_core::remove_event(int fd)
    {
        epoll_event ee{};
        epoll_ctl(this->ep_fd, EPOLL_CTL_DEL, fd, &ee);
        this->event_map.erase(fd);
    }

    void epoll_core::new_accept_event(int fd, sockaddr_in &addr, int &sock_fd, const coroutine::event_coroutine &cor,
                                      int &error_code)
    {
        epoll_event ee{};
        ee.data.fd = fd;
        ee.events = EPOLLIN;
        epoll_ctl(this->ep_fd, EPOLL_CTL_ADD, fd, &ee);
        this->event_map.emplace(fd, make_unique<event::accept_event>(fd, cor, sock_fd, addr, error_code));
    }

    void epoll_core::handle_read_event(event::event &event1)
    {
        auto &rd_event = dynamic_cast<event::read_event &>(event1);
        auto res = read(rd_event.get_fd(), rd_event.get_buffer(), rd_event.get_size());
        if (res < 0)
        {
            //throw runtime_error(strerror(errno));
            rd_event.set_error_code(res);
        }
        else
        {
            rd_event.set_error_code(0);
        }
        rd_event.set_res_size(res);
        rd_event.get_coroutine().resume();
    }

    void epoll_core::handle_write_event(event::event &event1)
    {
        auto &wt_event = dynamic_cast<event::write_event &>(event1);
        auto res = write(wt_event.get_fd(), wt_event.get_buffer(), wt_event.get_size());
        if (res < 0)
        {
            //throw runtime_error(strerror(errno));
            wt_event.set_error_code(res);
        }
        else
        {
            wt_event.set_error_code(0);
        }
        wt_event.set_res_size(res);
        wt_event.get_coroutine().resume();
    }

    void epoll_core::handle_accept_event(event::event &event1)
    {
        auto acc_event = dynamic_cast<event::accept_event &>(event1);
        socklen_t sock_len{0};
        sockaddr_in addr{};
        auto res = accept(acc_event.get_fd(), reinterpret_cast<sockaddr *>(&addr), &sock_len);
        if (res < 0)
        {
            acc_event.set_error_code(res);
        }
        else
        {
            acc_event.set_error_code(0);
        }
        acc_event.set_sock_fd(res);
        acc_event.set_sockaddr(addr);
        acc_event.get_coroutine().resume();
    }

    void epoll_core::handle_timer_event(event::event &event1)
    {

    }
}