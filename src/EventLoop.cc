#include "EventLoop.h"
#include "Poller.h"
#include "Acceptor.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

EventLoop::~EventLoop()
{
    //dtor
}

void EventLoop::loop()
{

    if(acceptor_!=NULL && acceptor_->isListening()==false)
    {
        if(acceptor_->listen(1024)==false)
        {
            printf("unknown error on bind:%s",strerror(errno));
            return;
        }
    }

    looping_ = true;
    while(!quit_)
    {
        activeChannels_.clear();
        if(poller_->poll(-1, &activeChannels_)>0)
        {
            for(ChannelList::iterator it = activeChannels_.begin();it!=activeChannels_.end();++it)
            {
                (*it)->handleEvent();
            }
        }
    }
}
