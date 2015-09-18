//
// Created by root on 8/23/15.
//

#include <boost/bind.hpp>
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Channel.h"
#include "Slogger.h"
#include "errno.h"
#include "error.h"
#include <stdlib.h>

TcpConnection::TcpConnection(const std::string& tname, EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr):
    name(tname),
    eventloop_(loop),
    fd_(sockfd),
    localAddr_(localAddr),
    peerAddr_(peerAddr),
    isConnected(false),
    buffer_(10*1000),
    dataQue()
{
    channel_ = loop->getPoller()->createChannel(sockfd, peerAddr);
    if(channel_==NULL)
    {
        logger::console->critical("TcpConnection createChannel failed {}",sockfd);
    }


    channel_->setReadCallback(boost::bind(&TcpConnection::handlRead, this));
    channel_->setWriteCallback(boost::bind(&TcpConnection::handlWrite, this));
}

TcpConnection::~TcpConnection()
{
    delete(channel_);
    std::string str = peerAddr_.getIpPortStr();
    logger::console->critical("TcpConnection Destroyed.peerAddr:{}",str);
}

void TcpConnection::handlRead()
{
    int buffCount=0;
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
    if(dataQue.front()!=NULL)
    {
        SendData* data = dataQue.front();
        int count = write(fd_,data->getWriteBuff(), data->getWriteSize());
        if(count>=0)
        {
            data->writeIndex += count;
        }
        else
        {
            if(errno==EBADF)
            {
                handleClose();
            }
            else if(errno !=EWOULDBLOCK)
            {
                char* errorStr = strerror(errno);
                logger::console->critical("TcpConnection Send",errorStr);
                free(errorStr);
            }
        }
    }
}

void TcpConnection::handleClose()
{
    closeCallback_(shared_from_this());
    close(fd_);
    eventloop_->getPoller()->removeChannel(channel_);
}



void TcpConnection::send(const boost::shared_ptr<std::string>& data)
{
    int count = write(fd_,data->c_str(),data->size());
    if(count>=0)
    {
        if(count==data->size())
        {
            writeCompleteCallback_(shared_from_this());
        }
        else
        {
            assert(count<data->size());
            SendData* sendData = new SendData(data, count);
            dataQue.push(sendData);
            channel_->enableWriteCallback();
        }

    }
    else
    {
        if(errno==EBADF)
        {
            handleClose();
        }
        else if(errno!=EWOULDBLOCK)
        {
            char* errorStr = strerror(errno);
            logger::console->critical("TcpConnection Send error {}",errorStr);
            free(errorStr);
        }

    }
}

