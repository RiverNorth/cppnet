#include "EpollPoller.h"
#include <sys/epoll.h>
#include <strings.h>
#include "Channel.h"

EpollPoller::~EpollPoller()
{
    //dtor
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
int EpollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
    int numEvents = ::epoll_wait(epollfd_,&events_.front(), events_.size(),timeoutMs);
    for(int i=0;i<numEvents;i++)
    {
        Channel* channel = (Channel*)events_[i].data.ptr;
        channel->setPollEvent(events_[i].events);
        activeChannels->push_back((Channel*)events_[i].data.ptr);
    }
    return numEvents;
}

bool EpollPoller::updateChannel(Channel* channel)
{
    if(channel->getIndex()==NewFd||channel->getIndex()==DeletedFd)
    {
        struct epoll_event event;
        bzero((void*)&event,sizeof(event));
        event.events=channel->getPollEvent();
        event.data.ptr = (void*)channel;
        event.data.fd = channel->getFd();
        if(::epoll_ctl(epollfd_,EPOLL_CTL_ADD,channel->getFd(),&event)<0)
        {
            return false;
        }
        channel->setIndex(AddedFd);
    }
    else if(channel->getIndex()==AddedFd)
    {
        struct epoll_event event;
        bzero((void*)&event,sizeof(event));
        event.events=channel->getPollEvent();
        event.data.ptr = (void*)channel;
        event.data.fd = channel->getFd();
        if(::epoll_ctl(epollfd_, EPOLL_CTL_MOD, channel->getFd(),&event))
        {
            return false;
        }
    }

    return true;
}

bool EpollPoller::removeChannel(Channel*)
{
    return true;
}

