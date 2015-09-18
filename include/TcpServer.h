//
// Created by root on 8/24/15.
//

#ifndef CPPNET_TCPSERVER_H
#define CPPNET_TCPSERVER_H

#include "Acceptor.h"
#include <unordered_map>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Callbacks.h"

class TcpConnection;
class Eventloop;

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
class TcpServer {
public:
    TcpServer(EventLoop* loop, const InetAddr& addr);
    bool start();
    void setNewConnectionCallback(TcpConnectionCallback& cb)
    {
        tcpConnectionCallback_ = cb;
    }
    void setNewMessageCallback(MessageCallback& cb)
    {
        messageCallback_ = cb;
    }
    void setConnectionCloseCallback(CloseCallback& cb)
    {
        closeCallback_ = cb;
    }
    void setWriteCompleteCallback(WriteCompleteCallback& cb)
    {
        writeCompleteCallback_ = cb;
    }
private:
    typedef std::unordered_map<std::string, TcpConnection*> ConnectionMap;

    void onNewConnectionCallback(int fd, const InetAddr& addr);
    void removeConnection(TcpConnectionPtr connection);

    EventLoop* eventloop_;
    Acceptor acceptor_;
    InetAddr serverAddr_;
    int connectId_;
    ConnectionMap connectionMap_;
    TcpConnectionCallback tcpConnectionCallback_;
    MessageCallback messageCallback_;
    CloseCallback closeCallback_;
    WriteCompleteCallback writeCompleteCallback_;
};


#endif //CPPNET_TCPSERVER_H
