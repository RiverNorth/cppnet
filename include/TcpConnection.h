//
// Created by root on 8/23/15.
//

#ifndef CPPNET_TCPCONNECTION_H
#define CPPNET_TCPCONNECTION_H

#include "InetAddr.h"
#include "socket.h"
#include "Channel.h"
#include "Callbacks.h"
#include <boost/enable_shared_from_this.hpp>
#include "Buffer.h"
class EventLoop;

class TcpConnection:public boost::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr);
    void setConnectionCallback(const TcpConnectionCallback& cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback_ = cb; }
    void setCloseCallback(const CloseCallback& cb){ closeCallback_ = cb;}
    void closeConnection(){handleClose();}
private:
    void handlRead();
    void handlWrite();
    void handleClose();

    EventLoop* eventloop_;
    int fd_;
    InetAddr localAddr_;
    InetAddr peerAddr_;
    Buffer buffer_;
    Channel* channel_;
    TcpConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;

    bool isConnected;
};


#endif //CPPNET_TCPCONNECTION_H
