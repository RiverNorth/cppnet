#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <vector>
#include "Channel.h"

class Poller;

class EventLoop
{
    public:
        EventLoop(Poller* poller):poller_(poller),looping_(false),quit_(false){};
        ~EventLoop();

        void loop();
        void quit();


    protected:
    private:
        typedef std::vector<Channel*> ChannelList;
        void handleRead();
        int wakeFd_;
        Poller* poller_;
        bool looping_;
        bool quit_;
        ChannelList activeChannels_;



};

#endif // EVENTLOOP_H
