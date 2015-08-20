#ifndef POLLER_H
#define POLLER_H
#include <vector>
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
    protected:
    private:
};

#endif // POLLER_H
