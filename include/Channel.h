#ifndef CHANNEL_H
#define CHANNEL_H
#include "Poller.h"
#include <boost/function.hpp>
#include <poll.h>
#include "EpollPoller.h"
#include "InetAddr.h"

class Channel
{
    public:
        typedef boost::function<void ()> EventCallback;
        static const int ReadEvent = POLLIN;
        static const int WriteEvent = POLLOUT;

        Channel(int fd,Poller* poller,const InetAddr& addr)
            :fd_(fd),
             poller_(poller),
             addr_(addr),
             index_(EpollPoller::NewFd),
             pollEvent_(0),  //for test,change later
             enableEvent_(0)
        {}
        virtual ~Channel();
        void setReadCallback(const EventCallback& cb){readCallback_ = cb;}
        void setWriteCallback(const EventCallback& cb){writeCallback_= cb;}
        //void setCloseCallback(EventCallback& cb){closeCallback_ = cb;}

        void enableReadCallback(){enableEvent_|= ReadEvent;updateChannelToPoller();}
        void enableWriteCallback(){enableEvent_ |= WriteEvent;updateChannelToPoller();}
        //void enableCloseCallback(){enableEvent_ |= CloseEvent;updateChannelToPoller();}
        void enableAllCallback()
        {
            enableEvent_ |= ReadEvent;
            enableEvent_ |= WriteEvent;
            //enableEvent_ |= CloseEvent;
            updateChannelToPoller();
        }

        void disableReadCallback(){enableEvent_&= ~ReadEvent;updateChannelToPoller();}
        void disableWriteCallback(){enableEvent_ &= ~WriteEvent;updateChannelToPoller();}
        //void disableCloseCallback(){enableEvent_ &= ~CloseEvent;updateChannelToPoller();}
        void disableAllEvent(){enableEvent_&=0;updateChannelToPoller();}

        void handleEvent();

        int getEnableEvent(){return enableEvent_;}
        void setPollEvent(int pollEvent){pollEvent_ = pollEvent;}
        int getPollEvent(){return pollEvent_;}
        int getFd(){return fd_;}
        void setIndex(int idx){index_ = idx;}
        int getIndex(){return index_;}
        const InetAddr* getAddr() const {return &addr_;};

    protected:
    private:

        bool updateChannelToPoller()
        {
            return poller_->updateChannel(this);
        }

        int fd_;
        Poller* poller_;
        ::InetAddr addr_;
        int index_;     //indicate the state of fd in poller
        int pollEvent_;
        int enableEvent_;
        EventCallback writeCallback_;
        EventCallback readCallback_;
        EventCallback closeCallback_;

};

#endif // CHANNEL_H
