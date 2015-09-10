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
    tcpSocket(sockfd),
    localAddr_(localAddr),
    peerAddr_(peerAddr),

    isConnected(false)
{
    channel_ = loop->getPoller()->createChannel(sockfd, peerAddr);
    if(channel_==NULL)
    {
        logger::console->critical("TcpConnection createChannel failed {}",sockfd);
    }
}

void TcpConnection::handlRead()
{

}

void TcpConnection::handlWrite()
{
}

void TcpConnection::handleClose()
{
}

