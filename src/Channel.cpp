#include "Channel.h"
#include <sys/poll.h>

Channel::~Channel()
{
    //dtor
}

void Channel::handleEvent()
{
    if((pollEvent_&POLLHUP)&&!(pollEvent_&POLLIN))
    {
        if(closeCallback_) closeCallback_();
    }

    if(pollEvent_&(POLLIN|POLLPRI))
    {
        if(readCallback_) readCallback_();
    }

    if(pollEvent_&POLLOUT)
    {
        if(writeCallback_) writeCallback_();
    }
}

