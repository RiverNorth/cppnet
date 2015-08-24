//
// Created by root on 8/23/15.
//

#include <boost/bind.hpp>
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Channel.h"

TcpConnection::TcpConnection(EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr):
    eventloop_(loop),
    tcpSocket(sockfd),
    localAddr_(localAddr),
    peerAddr_(peerAddr),
    channel_(sockfd,eventloop_->getPoller()),
    isConnected(false)
{
    channel_.setReadCallback(boost::bind(&TcpConnection::handlRead, this));
    channel_.setWriteCallback(boost:bind(&TcpConnection::handlWrite, this));
    channel_.setCloseCallback(boost::bind(&TcpConnection::handleClose, this));
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

