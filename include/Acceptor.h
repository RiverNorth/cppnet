#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <boost/function.hpp>
#include "noncopyable.h"
#include <string>
#include "Channel.h"
#include "InetAddr.h"
#include "Callbacks.h"

class EventLoop;
namespace fsociety
{
    namespace net
    {
        class Socket;
    }
}

class Acceptor:private Noncopyable
{
    public:
        Acceptor(EventLoop* loop, InetAddr const* addr);
        ~Acceptor();

        bool isListening(){ return isListening_;}
        bool listen(int backlogs);
        void setNewConnectionCallback(const NewConnectionCallback& cb){ newConnectionCallback_ =cb;}
        void handleRead();
    protected:
    private:
        EventLoop* eventLoop_;
        fsociety::net::Socket* listenSocket_;
        Channel* acceptChannel_;
        bool isListening_;
        NewConnectionCallback newConnectionCallback_;
};

#endif // ACCEPTOR_H
