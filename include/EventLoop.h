#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <vector>
#include "Channel.h"
#include "Acceptor.h"
class Poller;

class EventLoop
{
    public:
        EventLoop(Poller* poller):poller_(poller),looping_(false),quit_(false){};
        ~EventLoop();

        void loop();
        void quit();

        Poller* getPoller()
        {
            return poller_;
        }

        void setAcceptor(Acceptor* acceptor)
        {
            acceptor_ = acceptor;
            //poller_.updateChannel(acceptor_->)
        }
    protected:
    private:
        typedef std::vector<Channel*> ChannelList;
        void handleRead();
        int wakeFd_;
        Poller* poller_;
        Acceptor* acceptor_;
        bool looping_;
        bool quit_;

        ChannelList activeChannels_;



};

#endif // EVENTLOOP_H
