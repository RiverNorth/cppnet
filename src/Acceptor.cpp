#include "Acceptor.h"
#include <sys/socket.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include "socket.h"
#include "EventLoop.h"
#include <boost/bind.hpp>
#include "TcpConnection.h"

using namespace fsociety::net;

Acceptor::Acceptor(EventLoop* loop, InetAddr const* addr):eventLoop_(loop),isListening_(false)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
    {
        printf("create socket error:%s",strerror(errno));
        return;
    }
    listenSocket_ = new Socket(fd);
    listenSocket_->setNonBlocking();
    acceptChannel_ = new Channel(fd, loop->getPoller());
    if(!listenSocket_->bindAddress(addr);
    {
        printf("unknown error on bind:%s",strerror(errno));
    }
    Channel::EventCallback f = boost::bind(&Acceptor::handleRead,this);
    acceptChannel_->setReadCallback(f);
    acceptChannel_->enableReadCallback();
}

Acceptor::~Acceptor()
{
    //dtor
}

bool Acceptor::listen(int backlogs)
{
    if(listenSocket_->listen(backlogs))
    {
        isListening_ = true;
    }
    else
    {
        isListening_ = false;
    }
    return isListening_;
}


void Acceptor::handleRead()
{
    InetAddr addr;
    int fd = listenSocket_->accept(&addr);
    while(fd>0)
    {
        if(newConnectionCallback_)
            newConnectionCallback_(fd,addr);
        else
            close(fd);
        fd = listenSocket_->accept(&addr);
    }

}

