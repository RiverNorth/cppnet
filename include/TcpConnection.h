//
// Created by root on 8/23/15.
//

#ifndef CPPNET_TCPCONNECTION_H
#define CPPNET_TCPCONNECTION_H

#include "InetAddr.h"
#include "socket.h"
#include "Channel.h"
#include "Callbacks.h"

class EventLoop;

class TcpConnection {
public:
    TcpConnection(EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr);
    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }

    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }

    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }
private:
    void handlRead();
    void handlWrite();
    void handleClose();

    EventLoop* eventloop_;
    fsociety::net::Socket tcpSocket;
    InetAddr localAddr_;
    InetAddr peerAddr_;
    Channel channel_;
    bool isConnected;
};


#endif //CPPNET_TCPCONNECTION_H
