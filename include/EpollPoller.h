#ifndef EPOLLPOLLER_H
#define EPOLLPOLLER_H
#include "Poller.h"
#include <vector>
#include <sys/epoll.h>

class EpollPoller:public Poller
{
    public:
        static const int NewFd=0;
        static const int AddedFd=1;
        static const int DeletedFd=2;

        EpollPoller():epollfd_(::epoll_create1(EPOLL_CLOEXEC)),events_(INIT_EPOLL_EVENTS_SIZE){};
        virtual ~EpollPoller();
        virtual int poll(int timeoutMs, ChannelList* activeChannels);
        virtual bool updateChannel(Channel* channel);
        virtual bool removeChannel(Channel* channel);

    protected:
    private:
        static const int INIT_EPOLL_EVENTS_SIZE= 32;
        int epollfd_;
        std::vector<struct epoll_event> events_;

};
#endif // EPOLLPOLLER_H
