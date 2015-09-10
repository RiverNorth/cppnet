#ifndef POLLER_H
#define POLLER_H
#include <vector>
#include <unordered_map>
#include "InetAddr.h"
class Channel;

class Poller
{
    public:
        typedef std::vector<Channel*> ChannelList;
        Poller();
        virtual ~Poller();
        virtual int poll(int timeoutMs, ChannelList* activeChannels)=0;
        virtual bool updateChannel(Channel* channel)=0;
        virtual bool removeChannel(Channel*)=0;
        Channel* createChannel(int fd, const ::InetAddr& addr);
    protected:
        std::unordered_map<int,Channel*> channelMap_;
    private:
};

#endif // POLLER_H
