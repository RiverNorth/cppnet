#include "EpollPoller.h"
#include <sys/epoll.h>
#include <strings.h>
#include "Channel.h"
#include <stdio.h>

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
    printf("EpollPoller::poll\r\n");
    int numEvents = ::epoll_wait(epollfd_,&events_.front(), events_.size(),timeoutMs);
    for(int i=0;i<numEvents;i++)
    {
        Channel* channel = (Channel*)events_[i].data.ptr;
        channel->setPollEvent(events_[i].events);
        activeChannels->push_back((Channel*)events_[i].data.ptr);
    }
    printf("numEvents:%d\r\n",numEvents);
    return numEvents;
}

bool EpollPoller::updateChannel(Channel* channel)
{
    if(channel->getIndex()==NewFd||channel->getIndex()==DeletedFd)
    {
        struct epoll_event event;
        bzero((void*)&event,sizeof(event));
        event.events=channel->getEnableEvent();
        event.data.ptr = (void*)channel;
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
        event.events=channel->getEnableEvent();
        event.data.ptr = (void*)channel;
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

