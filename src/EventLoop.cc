#include "EventLoop.h"
#include "Poller.h"
EventLoop::~EventLoop()
{
    //dtor
}

void EventLoop::loop()
{
    looping_ = true;
    while(!quit_)
    {
        activeChannels_.clear();
        if(poller_->poll(0, &activeChannels_)>0)
        {
            for(ChannelList::iterator it = activeChannels_.begin();it!=activeChannels_.end();++it)
            {
                (*it)->handleEvent();
            }
        }
    }
}
