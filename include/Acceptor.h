#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <boost/function.hpp>
#include "noncopyable.h"
#include <string>
#include "Channel.h"


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
        typedef boost::function<void(fsociety::net::Socket* socket)> NewConnectionCallback;
        Acceptor(EventLoop* loop, std::string ip, uint16_t port);
        ~Acceptor();

        bool isListening(){ return isListening_;}
        bool listen(int backlogs);
        void setNewConnectionCallback(const NewConnectionCallback& cb){cb_ =cb;}
        void handleRead();
    protected:
    private:
        EventLoop* eventLoop_;
        fsociety::net::Socket* listenSocket_;
        Channel* acceptChannel_;
        bool isListening_;
        NewConnectionCallback cb_;
};

#endif // ACCEPTOR_H
