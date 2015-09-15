#include "socket.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "EpollPoller.h"
#include "EventLoop.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "InetAddr.h"
#include "Slogger.h"

using namespace fsociety::net;

void printWord(Channel* channel)
{
    char abc[50];
    bzero(abc, 50);
    int i = read(channel->getFd(),abc,50);
    if(i==0)
    {
        std::string ipStr = channel->getAddr()->getIpPortStr();
        logger::console->info("socket:{} closed",ipStr);
        close(channel->getFd());
    }
    else
    {
        printf("%s\n", abc);
    }
}

void printLog(int fd, const InetAddr& addr, Poller* poller)
{
    std::string ipStr = addr.getIpPortStr();
    logger::console->info("recieve conn from {}",ipStr);
    Channel* newChannel = poller->createChannel(fd, addr);
    Channel::EventCallback f = boost::bind(&printWord, newChannel);
    newChannel->setReadCallback(f);
    newChannel->enableReadCallback();
}

void forTest(int a,int b,int c)
{
    printf("%d,%d,%d\r\n",a,b,c);

}


int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    Socket s(fd);

    EpollPoller poller;
    EventLoop eventLoop(&poller);
    InetAddr inetAddr("127.0.0.1",9930);
    Acceptor acceptor(&eventLoop, &inetAddr);
    ::NewConnectionCallback f = boost::bind(&printLog,_1,_2, &poller);
    acceptor.setNewConnectionCallback(f);

    eventLoop.setAcceptor(&acceptor);
    eventLoop.loop();

/*
    Socket* socket = s.accept();
    if(socket!=NULL)
    {
        printf("socket accepted:ip(%s),port(%d)",socket->getIpStr().c_str(),socket->getPortNum());
        sleep(100);
        socket->close();
    }
*/
}


