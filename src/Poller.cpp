#include "Poller.h"
#include "logger.h"
#include "Channel.h"

Poller::Poller()
{
    //ctor
}

Poller::~Poller()
{
    //dtor
}

Channel* Poller::createChannel(int fd,const ::InetAddr& addr)
{
    if(channelMap_.find(fd)!=channelMap_.end())
    {
        logger::console->critical("createChannel fd{} already exsits",fd);
        return NULL;
    }

    Channel* channel = new Channel(fd, this, addr);
    channelMap_.insert({{fd,channel}});
    return channel;
}
