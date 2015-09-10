//
// Created by root on 8/24/15.
//

#ifndef CPPNET_TCPSERVER_H
#define CPPNET_TCPSERVER_H

#include "Acceptor.h"
#include <map>
#include <string>
class TcpConnection;
class Eventloop;
class TcpServer {
public:
    TcpServer(EventLoop* loop, const InetAddr& addr);
    bool start();
private:
    typedef std::map<std::string, TcpConnection*> ConnectionMap;
    EventLoop* eventloop_;
    Acceptor acceptor_;
    InetAddr serverAddr_;
    int connectId_;
    ConnectionMap connectionMap_;

    void onNewConnectionCallback(int fd, const InetAddr& addr);

    void handleReadCallback()
    {

    }

    void handleWriteCallback()
    {

    }

    void handleCloseCallback()
    {

    }

};


#endif //CPPNET_TCPSERVER_H
