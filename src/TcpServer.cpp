//
// Created by root on 8/24/15.
//

#include <EventLoop.h>
#include "TcpServer.h"
#include <boost/bind.hpp>
#include <stdio.h>
#include "EventLoop.h"
#include "TcpConnection.h"
#include <errno.h>

TcpServer::TcpServer(EventLoop* loop, const InetAddr& addr)
    :eventloop_(loop),
     acceptor_(loop,&addr),
     serverAddr_(addr),
     connectId_(1),
     ConnectionMap()
{
    //acceptor_.setNewConnectionCallback(boost::bind(onNewConnectionCallback, this));
    ConnectionMap.reserve(10000);
}

bool TcpServer::start()
{
    if(!acceptor_.listen(200))
    {
        char* error = strerror(errno);
        logger::console->critical("socket listen failed {}",error);
        free(error);
        return false;
    }
    eventloop_->loop();
    return true;
}


void TcpServer::onNewConnectionCallback(int fd, const InetAddr& addr)
{
    char buf[32];
    bzero((void*)buf, 32);
    std::string name = snprintf(buf, 32, "%s:%d",addr.getIpPortStr(),connectId_);
    logger::console->info("NewConnection:{}",name);
    ++connectId_;
    InetAddr localAddr(serverAddr_);
    TcpConnection* tcpConnection= new TcpConnection(name, eventloop_, fd, serverAddr_, addr);
    connectionMap_[name] = tcpConnection;
    tcpConnection->setCloseCallback(boost::bind(&TcpServer::removeConnection, this,_1));
    tcpConnection->setMessageCallback(messageCallback_);
    tcpConnection->setWriteCompleteCallback(writeCompleteCallback_);

}

void TcpServer::removeConnection(TcpConnectionPtr connection)
{
    connectionMap_.erase(connection->name);
}

