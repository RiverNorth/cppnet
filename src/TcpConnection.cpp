//
// Created by root on 8/23/15.
//

#include <boost/bind.hpp>
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Channel.h"
#include "logger.h"

TcpConnection::TcpConnection(EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr):
    eventloop_(loop),
    fd_(sockfd),
    localAddr_(localAddr),
    peerAddr_(peerAddr),
    isConnected(false),
    buffer_(10*1000)
{
    channel_ = loop->getPoller()->createChannel(sockfd, peerAddr);
    if(channel_==NULL)
    {
        logger::console->critical("TcpConnection createChannel failed {}",sockfd);
    }

    channel_->setReadCallback(boost::bind(&TcpConnection::handlRead, this));
    channel_->setWriteCallback(boost::bind(&TcpConnection::handlWrite, this));
}

void TcpConnection::handlRead()
{
    size_t buffCount=0;
    char* rawBuffer = buffer_.getWriteBuff(buffCount);
    size_t count = read(fd_, rawBuffer, buffCount);
    if(count==0)
    {
        handleClose();
    }
    else
    {
        messageCallback_(shared_from_this());
    }
}

void TcpConnection::handlWrite()
{

}

void TcpConnection::handleClose()
{
    closeCallback_(shared_from_this());
}

