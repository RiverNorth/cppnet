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

using namespace fsociety::net;

void printWord(Channel* channel)
{
    char abc[1];
    bzero(abc, 1);
    int i = read(channel->getFd(),abc,1);
    if(i==0)
    {
        printf("socket closed\r\n");
        close(channel->getFd());
    }
    else
    {
        printf("%s", abc);
    }
}

void printLog(int fd, const InetAddr& addr, Poller* poller)
{
    printf("recieve conn from %s\r\n",addr.getIpPortStr().c_str());
    Channel* newChannel = new Channel(fd,poller);
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
    Acceptor acceptor(&eventLoop,"127.0.0.1",9930);
    Acceptor::NewConnectionCallback f = boost::bind(&printLog,_1,_2, &poller);
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


