//
// Created by root on 8/24/15.
//

#include <EventLoop.h>
#include "TcpServer.h"
#include <boost/bind.hpp>
#include <stdio.h>
#include "EventLoop.h"
#include "TcpConnection.h"

TcpServer::TcpServer(EventLoop* loop, const InetAddr& addr)
    :eventloop_(loop),
     acceptor_(loop,&addr),
     serverAddr_(addr),
     connectId_(1)
{
    //acceptor_.setNewConnectionCallback(boost::bind(onNewConnectionCallback, this));
}

bool TcpServer::start()
{
    if(!acceptor_.listen(200))
    {
        printf("socket listen failed\r\n");
        return false;
    }
    eventloop_->loop();
    return true;
}


void TcpServer::onNewConnectionCallback(int fd, const InetAddr& addr)
{
    char buf[32];
    snprintf(buf,sizeof(buf),"%s#%d",addr.getIp().c_str(),connectId_);
    ++connectId_;
    InetAddr localAddr(serverAddr_);
    std::string name = buf;
    TcpConnection* tcpConnection= new TcpConnection(eventloop_, fd, serverAddr_, addr);
    connectionMap_[name] =tcpConnection;
}