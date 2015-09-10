#include "Acceptor.h"
#include <sys/socket.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include "socket.h"
#include "EventLoop.h"
#include <boost/bind.hpp>
#include "TcpConnection.h"
#include "logger.h"
#include "EventLoop.h"
#include <string>


using namespace fsociety::net;

Acceptor::Acceptor(EventLoop* loop, ::InetAddr const* addr):eventLoop_(loop),isListening_(false)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0)
    {
        printf("create socket error:%s",strerror(errno));
        return;
    }
    listenSocket_ = new Socket(fd);
    listenSocket_->setNonBlocking();

    acceptChannel_ = loop->getPoller()->createChannel(fd,*addr);

    if(acceptChannel_==NULL)
    {
        logger::console->critical("Acceptor createChannel Null fd{}",fd);
    }

    if(!listenSocket_->bindAddress(addr))
    {
        char* error = strerror(errno);
        std::string ipPortStr = addr->getIpPortStr();
        logger::console->critical("error on bind {}:reason{}",ipPortStr,error);
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
    ::InetAddr addr;
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

