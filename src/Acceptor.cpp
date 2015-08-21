#include "Acceptor.h"
#include <sys/socket.h>
#include <string.h>
#include <sys/errno.h>
#include <stdio.h>
#include "socket.h"
#include "EventLoop.h"
#include <boost/bind.hpp>

using namespace fsociety::net;

Acceptor::Acceptor(EventLoop* loop, std::string ipStr, uint16_t port):eventLoop_(loop),isListening_(false)
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
    if(!listenSocket_->bindAddress(ipStr.c_str(),port))
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
    Socket* newSocket = listenSocket_->accept();
    while(newSocket!=NULL)
    {
        if(cb_)
        {
            cb_(newSocket);
        }
        else
        {
            delete newSocket;
        }
        newSocket = listenSocket_->accept();
    }
}

