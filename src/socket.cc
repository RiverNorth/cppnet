#include "socket.h"
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

using namespace fsociety;
using namespace fsociety::net;

Socket::Socket(int sockfd,struct sockaddr_in addr):socketfd_(sockfd),port_(ntohs(addr.sin_port))
{
    char ip[32];
	::inet_ntop(AF_INET,(void*)&addr.sin_port,ip,32);
    ipAddr_ = std::string(ip);
}
std::string Socket::getIpStr()
{
	return ipAddr_;
}

uint16_t Socket::getPortNum()
{
    return port_;
}

bool Socket::setNonBlocking()
{
    int flags = ::fcntl(socketfd_,F_GETFL);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(socketfd_,F_SETFL,flags);
    if(ret==-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Socket::bindAddress(const std::string& ipAddress, uint16_t port)
{
    if(!setReuseAddr())
    {
        printf("reuse addr faild;\r\n");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    addr.sin_port = htons(port);
    if(bind(socketfd_,(struct sockaddr*)&addr, sizeof(struct sockaddr))==-1)
    {
        return false;
    }
    else
    {
        ipAddr_ = ipAddress;
        port_ = port;
        return true;
    }
}

bool Socket::setReuseAddr()
{
    int optval = 1;
    if(::setsockopt(socketfd_,SOL_SOCKET,SO_REUSEADDR, &optval,static_cast<socklen_t>(sizeof(optval)))==0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Socket::listen(int backlog)
{
    if(::listen(socketfd_,backlog)!=0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Socket* Socket::accept()
{
    struct sockaddr_in addr;
    socklen_t len = static_cast<socklen_t> (sizeof(addr));
    int fd = ::accept(socketfd_,(struct sockaddr*)&addr,&len);
    if(fd==-1)
    {
        return NULL;
    }
    else
    {
        return new Socket(fd, addr);
    }
}

bool Socket::close()
{
    if(::close(socketfd_)==-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
