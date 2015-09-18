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
#include <queue>
#include <list>
class EventLoop;

class TcpConnection:public boost::enable_shared_from_this<TcpConnection>{
public:
    typedef boost::shared_ptr<std::string> string_ptr;
    class SendData
    {
    public:
        std::string name;
        string_ptr ptr;
        uint32_t writeIndex;
        std::string::size_type dataSize;
        SendData(const string_ptr& tPtr, uint32_t tWriteIndex):ptr(tPtr),writeIndex(tWriteIndex),dataSize(tPtr->size())
        {
        }

        uint32_t getWriteSize()
        {
            return dataSize - writeIndex;
        }

        const char* getWriteBuff()
        {
            return ptr->c_str()+writeIndex;
        }
    };
    typedef std::queue<SendData*,std::list<SendData*> > DataQue;

    TcpConnection(const std::string& tname, EventLoop* loop, int sockfd,const InetAddr& localAddr, const InetAddr& peerAddr);
    ~TcpConnection();
    void setConnectionCallback(const TcpConnectionCallback& cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback_ = cb; }
    void setCloseCallback(const CloseCallback& cb){ closeCallback_ = cb;}
    void closeConnection(){handleClose();}
    void send(const boost::shared_ptr<std::string>& data);

    const std::string name;
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

    DataQue dataQue;
    bool isConnected;
};


#endif //CPPNET_TCPCONNECTION_H
